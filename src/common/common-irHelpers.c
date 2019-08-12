/*
    Authored 2015-2018, Phillip Stanley-Marbell. Modified 2017, Jonathan Lim.

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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "flextypes.h"
#include "flexerror.h"
#include "flex.h"
#include "common-errors.h"
#include "noisy-timeStamps.h"
#include "common-timeStamps.h"
#include "common-data-structures.h"
#include "common-irHelpers.h"
#include "common-lexers-helpers.h"


/*
 *	This implements a very shallow copy: all the constituent pointers
 *	are still the original references. The only thing new are the
 *	child pointers, which get reset.
 */
IrNode *
shallowCopyIrNode(State *  N, IrNode *  original)
{
	IrNode *	clone = calloc(1, sizeof(IrNode));
	if (clone == NULL)
	{
		fatal(N, Emalloc);
	}

	memcpy(clone, original, sizeof(IrNode));
	clone->irLeftChild = NULL;
	clone->irRightChild = NULL;

	return clone;
}


IrNode *
genIrNode(State *  N, IrNodeType type, IrNode *  irLeftChild, IrNode *  irRightChild, SourceInfo *  sourceInfo)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyGenNoisyIrNode);

	IrNode *		node;

	node = (IrNode *) calloc(1, sizeof(IrNode));
	if (node == NULL)
	{
		fatal(N, Emalloc);

		/*	Not reached	*/
	}

	node->type		= type;
	node->sourceInfo	= sourceInfo;
	node->irLeftChild	= irLeftChild;
	node->irRightChild	= irRightChild;

	if (irLeftChild != NULL)
	{
		irLeftChild->irParent = node;
	}

	if (irRightChild != NULL)
	{
		irRightChild->irParent = node;
	}

	/*
	 *	Not madatory, but provides higher-fidelity attribution, by making 
	 *	sure that any time between here and next stamping is not attributed
	 *	to genIrNode().
	 */
	//NoisyTimeStampTraceMacro(kNoisyTimeStampKeyUnknown);


	return node;
}


void
errorUseBeforeDefinition(State *  N, const char *  identifier)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserErrorUseBeforeDefinition);

	flexprint(N->Fe, N->Fm, N->Fperr, Eusedef, identifier);
	flexprint(N->Fe, N->Fm, N->Fperr, "\n");
}

void
errorMultiDefinition(State *  N, Symbol *  symbol)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserErrorMultiDefinition);

	flexprint(N->Fe, N->Fm, N->Fperr, Emultidef, symbol->identifier, symbol->sourceInfo->fileName, symbol->sourceInfo->lineNumber, symbol->sourceInfo->columnNumber);
	flexprint(N->Fe, N->Fm, N->Fperr, " ");
	flexprint(N->Fe, N->Fm, N->Fperr, Epreviousdef, symbol->definition->sourceInfo->fileName, symbol->definition->sourceInfo->lineNumber, symbol->definition->sourceInfo->columnNumber);
	flexprint(N->Fe, N->Fm, N->Fperr, "\n");
	flexprint(N->Fe, N->Fm, N->Fperr, "\n");
}

IrNode*
findNthIrNodeOfTypes(State * N, IrNode * root, IrNodeType productionOrToken, int firsts[kNoisyIrNodeTypeMax][kNoisyIrNodeTypeMax], int nth)
{
	int ith = nth; // copy so we do not modify the caller's count variable
	return findNthIrNodeOfTypesHelper(N, root, productionOrToken, firsts, &ith);
}

IrNode*
findNthIrNodeOfTypesHelper(State * N, IrNode * root, IrNodeType productionOrToken, int firsts[kNoisyIrNodeTypeMax][kNoisyIrNodeTypeMax], int *nth)
{
	assert(root != NULL);
	for (int i = 0; i < kNoisyIrNodeTypeMax && firsts[productionOrToken][i] != kNoisyIrNodeTypeMax; i++)
	{
		if (firsts[productionOrToken][i] == root->type)
		{
			if(*nth == 0)
			{
				return root;
			}
			*nth = *nth - 1;

			break;
		}
	}

	IrNode * nthNode;
	if (root->irLeftChild != NULL &&\
		(nthNode = findNthIrNodeOfTypesHelper(N, root->irLeftChild, productionOrToken, firsts, nth)) != NULL)
	{
		return nthNode;
	}

	if (root->irRightChild != NULL &&\
		(nthNode = findNthIrNodeOfTypesHelper(N, root->irRightChild, productionOrToken, firsts, nth)) != NULL)
	{
		return nthNode;
	}

	return NULL;
}

IrNode*
findNthIrNodeOfType(State * N, IrNode * root, IrNodeType expectedType, int nth)
{
	int ith = nth;
	return findNthIrNodeOfTypeHelper(N, root, expectedType, &ith);
}

IrNode*
findNthIrNodeOfTypeHelper(State * N, IrNode * root, IrNodeType expectedType, int* nth)
{
	if (root->type == expectedType)
	{
		if(*nth == 0)
		{
			return root;
		}
		*nth = *nth - 1;
	}

	IrNode * nthNode;
	if (root->irLeftChild != NULL &&\
		(nthNode = findNthIrNodeOfTypeHelper(N, root->irLeftChild, expectedType, nth)) != NULL)
	{
		return nthNode;
	}

	if (root->irRightChild != NULL &&\
		(nthNode = findNthIrNodeOfTypeHelper(N, root->irRightChild, expectedType, nth)) != NULL)
	{
		return nthNode;
	}

	return NULL;
}

int
depthFirstWalk(State *  N, IrNode *  node, int Counter)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserDepthFirstWalk);

	if (node->irLeftChild == NULL && node->irRightChild == NULL && node->type==kNewtonIrNodeType_Tidentifier && node->isVisited==false)
	{
		node->isVisited=true;
		Counter+=1

	}
	depthFirstWalk(N, node->irRightChild);

	depthFirstWalk(N, node->irLeftChild);

	return Counter
}

IrNode *
depthFirstWalkNoLeftChild(State *  N, IrNode *  node)
{
	/*
	 *	Function identical to depthFirstWalk(), except this doesn't
	 *	check irLeftChild.
	 */
	TimeStampTraceMacro(kNoisyTimeStampKeyParserDepthFirstWalk);

	if (node->irRightChild == NULL)
	{
		return node;
	}

	return depthFirstWalkNoLeftChild(N, node->irRightChild);
}

void
addLeaf(State *  N, IrNode *  parent, IrNode *  newNode)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserAddLeaf);

	IrNode *	node = depthFirstWalk(N, parent);

	if (node == NULL)
	{
		fatal(N, Esanity);
	}

	if (node->irLeftChild == NULL)
	{
		node->irLeftChild = newNode;

		return;
	}

	node->irRightChild = newNode;
}

void
addLeafWithChainingSeq(State *  N, IrNode *  parent, IrNode *  newNode)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserAddLeafWithChainingSeq);

	IrNode *	node = depthFirstWalk(N, parent);

	if (node == NULL)
	{
		fatal(N, Esanity);
	}

	if (node->irLeftChild == NULL)
	{
		node->irLeftChild = newNode;

		return;
	}

	node->irRightChild = genIrNode(N,	kNoisyIrNodeType_Xseq,
						newNode /* left child */,
						NULL /* right child */,
						lexPeek(N, 1)->sourceInfo /* source info */);
}

void
addLeafWithChainingSeqNoLex(State *  N, IrNode *  parent, IrNode *  newNode, SourceInfo *  srcInfo)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserAddLeafWithChainingSeq);

	IrNode *	node = depthFirstWalk(N, parent);

	if (node == NULL)
	{
		fatal(N, Esanity);
	}

	if (node->irLeftChild == NULL)
	{
		node->irLeftChild = newNode;

		return;
	}

	node->irRightChild = genIrNode(N,	kNoisyIrNodeType_Xseq,
						newNode /* left child */,
						NULL /* right child */,
						srcInfo /* source info */);
}

bool
peekCheck(State *  N, int lookAhead, IrNodeType expectedType)
{
	TimeStampTraceMacro(kNoisyTimeStampKeyParserPeekCheck);

	if (lexPeek(N, lookAhead) == NULL)
	{
		return false;
	}

	return (lexPeek(N, lookAhead)->type == expectedType);
}

IrNodeType
getTypeFromOperatorSubtree(State *  N, IrNode *  n)
{
	/*
	 *	All operators are tucked under a production, so dig through the left subtree
	 *	to find the actual operator type:
	 */
	while (L(n) != NULL)
	{
		n = L(n);
	}

	return n->type;
}