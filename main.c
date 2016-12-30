/*
	Authored 2015. Phillip Stanley-Marbell.

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	*	Redistributions of source code must retain the above
		copyright notice, this list of conditions and the following
		disclaimer.

	*	Redistributions in binary form must reproduce the above
		copyright notice, this list of conditions and the following
		disclaimer in the documentation and/or other materials
		provided with the distribution.

	*	Neither the name of the author nor the names of its
		contributors may be used to endorse or promote products
		derived from this software without specific prior written
		permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <getopt.h>
#include <setjmp.h>
#include <stdint.h>
#include "flextypes.h"
#include "flexerror.h"
#include "flex.h"
#include "noisy-errors.h"
#include "version.h"
#include "noisy-timeStamps.h"
#include "noisy.h"
#include "noisy-parser.h"
#include "noisy-lexer.h"
#include "noisy-symbolTable.h"
#include "noisy-irPass-helpers.h"
#include "noisy-irPass-dotBackend.h"
#include "noisy-irPass-protobufBackend.h"

#include "noisyconfig-parser.h"
#include "noisyconfig-lexer.h"
#include "noisyconfig-symbolTable.h"

//extern const char	gNoisyEol[];
//extern const char	gNoisyWhitespace[];
//extern const char	gNoisyStickies[];

static void		usage(NoisyState *  N);
static void		processFile(NoisyState *  N, char *  filename);
static void		version(NoisyState *  N);


// static void		usage(NoisyState *  N);
static void		processConfigFile(NoisyState *  N);
// static void		version(NoisyState *  N);

static void     recurseDimensions(NoisyState * N, NoisyScope * topScope);
static void     recursePhysics(NoisyState * N, NoisyScope * topScope);

static void
recurseDimensions(NoisyState * N, NoisyScope * topScope)
{
    Dimension * curDimension = topScope->firstDimension;
    if (curDimension == NULL)
		flexprint(N->Fe, N->Fm, N->Fperr, "topscope dimension doesn't exist\n");

    while (curDimension != NULL) {
		flexprint(N->Fe, N->Fm, N->Fperr, "dimension %s %x\n", curDimension->identifier, curDimension);
        curDimension = curDimension->next;
    }
}

static void
recursePhysics(NoisyState * N, NoisyScope * topScope)
{
    Physics * curPhysics = topScope->firstPhysics;
    if (curPhysics == NULL)
		flexprint(N->Fe, N->Fm, N->Fperr, "topscope physics doesn't exist\n");
    
    while (curPhysics != NULL) {
		flexprint(N->Fe, N->Fm, N->Fperr, "physics %s\n", curPhysics->identifier);
		flexprint(N->Fe, N->Fm, N->Fperr, "alias %s\n", curPhysics->dimensionAlias);
		flexprint(N->Fe, N->Fm, N->Fperr, "isvector %d\n", curPhysics->isVector);
        if (curPhysics->vectorCounterpart)
		    flexprint(N->Fe, N->Fm, N->Fperr, "vectorCounterpart %s\n", curPhysics->vectorCounterpart->identifier);
        if (curPhysics->scalarCounterpart)
		    flexprint(N->Fe, N->Fm, N->Fperr, "scalarCounterpart %s\n", curPhysics->scalarCounterpart->identifier);
        
        Dimension * curDimension = curPhysics->numeratorDimensions;
        while (curDimension != NULL) {
	    	flexprint(N->Fe, N->Fm, N->Fperr, "numerator dimension %s %d %x\n", curDimension->identifier, curDimension->primeNumber, curDimension);
            curDimension = curDimension->next;
        }
        
        curDimension = curPhysics->denominatorDimensions;
        while (curDimension != NULL) {
	    	flexprint(N->Fe, N->Fm, N->Fperr, "denominator dimension %s %d %x\n", curDimension->identifier, curDimension->primeNumber, curDimension);
            curDimension = curDimension->next;
        }
        
        curPhysics = curPhysics->next;
    }

    IntegralList* curVectorIntegralList = N->vectorIntegralLists;
    while (curVectorIntegralList != NULL)
    {
        Physics * curIntegralPhysics = curVectorIntegralList->head;
        while (curIntegralPhysics != NULL)
        {
	    	flexprint(N->Fe, N->Fm, N->Fperr, "vector integral element %s\n", curIntegralPhysics->identifier);
            curIntegralPhysics = curIntegralPhysics->next;
        }
    
        curVectorIntegralList = curVectorIntegralList->next; 
    }
    
    IntegralList* curScalarIntegralList = N->scalarIntegralLists;
    while (curScalarIntegralList != NULL)
    {
        Physics * curIntegralPhysics = curScalarIntegralList->head;
        while (curIntegralPhysics != NULL)
        {
	    	flexprint(N->Fe, N->Fm, N->Fperr, "scalar integral element %s\n", curIntegralPhysics->identifier);
            curIntegralPhysics = curIntegralPhysics->next;
        }
    
        curScalarIntegralList = curScalarIntegralList->next; 
    }
    
    return;
}

int
main(int argc, char *argv[])
{
	int			jumpParameter;
	NoisyState *		N;

	N = noisyInit(kNoisyModeDefault);
	
    if (N == NULL)
	{
		noisyFatal(NULL, Emalloc);

		/*	Not reached	*/
		noisyConsolePrintBuffers(N);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		char			tmp;
		char *			ep = &tmp;
		int			optionIndex	= 0, c;
		static struct option	options[]	=
		{
			{"verbose",		required_argument,	0,	'v'},
			{"help",		no_argument,		0,	'h'},
			{"version",		no_argument,		0,	'V'},
			{"dot",			required_argument,	0,	'd'},
			{"bytecode",		required_argument,	0,	'b'},
			{"trace",		no_argument,		0,	't'},
			{"statistics",		no_argument,		0,	's'},
			{"optimize",		required_argument,	0,	'O'},
			{0,			0,			0,	0}
		};

		c = getopt_long(argc, argv, "v:hVd:b:stO:", options, &optionIndex);

		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			case 0:
			{
				/*
				 *	Not sure what the expected behavior for getopt_long is here...
				 */
				break;
			}

			case 'h':
			{
				usage(N);
				noisyConsolePrintBuffers(N);
				exit(EXIT_SUCCESS);

				/*	Not reached 	*/
				break;
			}

			case 'V':
			{
				version(N);
				noisyConsolePrintBuffers(N);
				exit(EXIT_SUCCESS);

				/*	Not reached 	*/
				break;
			}

			case 'd':
			{
				N->irBackends |= kNoisyIrBackendDot;
				
				//TODO: rather than accepting the raw enum value as integer, accept string and compare to table of options
				uint64_t tmpInt = strtoul(optarg, &ep, 0);
				if (*ep == '\0')
				{
					N->dotDetailLevel = tmpInt;
				}
				else
				{
					usage(N);
					noisyConsolePrintBuffers(N);
					exit(EXIT_FAILURE);
				}

				break;
			}

			case 'b':
			{
				N->irBackends |= kNoisyIrBackendProtobuf;
				N->outputFilePath = optarg;

				break;
			}

			case 't':
			{
				N->mode |= kNoisyModeCallTracing;
				N->mode |= kNoisyModeCallStatistics;
				noisyTimestampsInit(N);

				break;
			}

			case 's':
			{
				N->mode |= kNoisyModeCallStatistics;
				noisyTimestampsInit(N);

				break;
			}

			case 'v':
			{
				uint64_t tmpInt = strtoul(optarg, &ep, 0);
				if (*ep == '\0')
				{
					/*
					 *	The verbosity bitmaps are:
					 *
					 *		kNoisyVerbosityAST
					 *		kNoisyVerbosityFF
					 *		kNoisyVerbosityLex
					 *		kNoisyVerbosityParse
					 */

					N->verbosityLevel = tmpInt;
				}
				else
				{
					usage(N);
					noisyConsolePrintBuffers(N);
					exit(EXIT_FAILURE);
				}

				break;
			}

			case 'O':
			{
				//TODO: define a structured way for which passes depend on which

				/*
				 *	Implies the following (basic) passes:
				 */
				//N->irPasses |= xxx;
				//N->irPasses |= yyy;

				uint64_t tmpInt = strtoul(optarg, &ep, 0);
				if (*ep == '\0')
				{
					N->optimizationLevel = tmpInt;
				}
				else
				{
					usage(N);
					noisyConsolePrintBuffers(N);
					exit(EXIT_FAILURE);
				}

				break;
			}

			case '?':
			{
				/*
				 *    getopt_long() should have already printed an error message.
				 */
				usage(N);
				noisyConsolePrintBuffers(N);
				exit(EXIT_FAILURE);

				break;
			}

			default:
			{
				usage(N);
				noisyConsolePrintBuffers(N);
				exit(EXIT_FAILURE);
			}
		}
	}

    processConfigFile(N);

	if (optind < argc)
	{
		while (optind < argc)
		{
			jumpParameter = setjmp(N->jmpbuf);
			if (!jumpParameter)
			{
				processFile(N, argv[optind++]);
			}
			else
			{
				//TODO: we could intelligently use the incoming jumpParameter

				/*	Return again after longjmp	*/
			}
		}
	}
	else
	{
		flexprint(N->Fe, N->Fm, N->Fperr, "\n%s\n", Enoinput);
		usage(N);
		noisyConsolePrintBuffers(N);
		exit(EXIT_FAILURE);
	}

	if (!(N->mode & kNoisyModeCGI))
	{
		noisyConsolePrintBuffers(N);
	}

	return 0;
}

/*
 * TODO: change this to be more flexible and take an arg from command line
 * https://github.com/phillipstanleymarbell/Noisy-lang-compiler/issues/28
 */
static void
processConfigFile(NoisyState *  N)
{

    char * fileName = "Examples/fullExamples2.nc";

	/*
	 *	Tokenize input, then parse it and build AST + symbol table.
	 */
	noisyConfigLexInit(N, fileName);

	/*
	 *	Create a top-level scope, then parse.
	 */
	N->noisyConfigIrTopScope = noisyConfigSymbolTableAllocScope(N);
	N->noisyConfigIrRoot = noisyConfigParse(N, N->noisyConfigIrTopScope);


	/*
	 *	Run passes requested in the command line flags.
	 */
	noisyRunPasses(N);

    recurseDimensions(N, N->noisyConfigIrTopScope);
    recursePhysics(N, N->noisyConfigIrTopScope);

	/*
	 *	Bytecode backend. Emit IR in protobuf.
	 */
	// if (N->irBackends & kNoisyConfigIrBackendProtobuf)
	// {
	// 	noisyConfigIrPassProtobufBackend(N);
	// }



	/*
	 *	Dot backend.
	 */
	if (N->irBackends & kNoisyIrBackendDot)
	{
		fprintf(stdout, "%s\n", noisyIrPassDotBackend(N));
	}
    


	// if (N->mode & kNoisyConfigModeCallTracing)
	// {
	// 	noisyConfigTimeStampDumpTimeline(N);
	// }
    
    noisyConsolePrintBuffers(N);
}

static void
processFile(NoisyState *  N, char *  fileName)
{
	/*
	 *	Tokenize input, then parse it and build AST + symbol table.
	 */
	noisyLexInit(N, fileName);

	/*
	 *	Create a top-level scope, then parse.
	 */
	N->noisyIrTopScope = noisySymbolTableAllocScope(N);
	N->noisyIrRoot = noisyParse(N, N->noisyIrTopScope);


	/*
	 *	Run passes requested in the command line flags.
	 */
	noisyRunPasses(N);


	/*
	 *	We don't put the following into noisyRunPasses() because they are not general-purpose
	 */


	/*
	 *	Bytecode backend. Emit IR in protobuf.
	 */
	if (N->irBackends & kNoisyIrBackendProtobuf)
	{
		noisyIrPassProtobufBackend(N);
	}


	/*
	 *	Dot backend.
	 */
	if (N->irBackends & kNoisyIrBackendDot)
	{
		fprintf(stdout, "%s\n", noisyIrPassDotBackend(N));
	}


	if (N->mode & kNoisyModeCallTracing)
	{
		noisyTimeStampDumpTimeline(N);
	}

	if (N->mode & kNoisyModeCallStatistics)
	{
		uint64_t	irNodeCount = 0, symbolTableNodeCount = 0;


		noisyTimeStampDumpResidencies(N);

		irNodeCount = noisyIrPassHelperIrSize(N, N->noisyIrRoot);
		symbolTableNodeCount = noisyIrPassHelperSymbolTableSize(N, N->noisyIrTopScope);


		flexprint(N->Fe, N->Fm, N->Fpinfo, "Intermediate Representation Information:\n\n");
		flexprint(N->Fe, N->Fm, N->Fpinfo, "    IR node count                        : %llu\n", irNodeCount);
		flexprint(N->Fe, N->Fm, N->Fpinfo, "    Symbol Table node count              : %llu\n", symbolTableNodeCount);

		/*
		 *	Libflex malloc statistics:
		 */
		if (N->Fm->debug)
		{
			flexmblocksdisplay(N->Fe, N->Fm, N->Fperr);
		}
	}
}


static void
version(NoisyState *  N)
{
	flexprint(N->Fe, N->Fm, N->Fperr, "\nNoisy version %s.\n\n", kNoisyVersion);
}


static void
usage(NoisyState *  N)
{
	version(N);
	flexprint(N->Fe, N->Fm, N->Fperr,	"Usage:    noisy [ (--help, -h)                                       \n"
						"                | (--version, --V)                                   \n"
						"                | (--verbose <level>, -v <level>)                    \n"
						"                | (--dot <level>, -d <level>)                        \n"
						"                | (--bytecode <output file name>, -b <output file name>)\n"
						"                | (--optimize <level>, -O <level>)                   \n"
						"                | (--trace, -t)                                      \n"
						"                | (--statistics, -s) ]                               \n"
						"                                                                     \n"
						"              <filenames>\n\n");
}
