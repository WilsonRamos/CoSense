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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdint.h>
#include "flextypes.h"
#include "flexerror.h"
#include "flex.h"
#include "noisyconfig-errors.h"
#include "version.h"
#include "noisyconfig.h"
#include "noisyconfig-symbolTable.h"


/*
 *	TODO: need to tag scopes corresponding to progtypes with a name, so
 *	that when we want to lookup a progtype-qualified-name in symtab, we
 *	can use the "a" of "a->b" to lookup, and get the type structure of
 *	"b".  See, e.g., comments at P_TYPENAME in noisyConfig-irPass-cBackend.
 */


NoisyConfigScope *
noisyConfigSymbolTableAllocScope(NoisyConfigState *  N)
{
	NoisyConfigScope *	newScope;

	newScope = (NoisyConfigScope *)calloc(1, sizeof(NoisyConfigScope));
	if (newScope == NULL)
	{
		noisyConfigFatal(N, Emalloc);
	}

	return newScope;
}


NoisyConfigSymbol *
noisyConfigSymbolTableAddOrLookupSymbolForToken(NoisyConfigState *  N, NoisyConfigScope *  scope, NoisyConfigToken *  token)
{
	NoisyConfigSymbol *	newSymbol;

	newSymbol = (NoisyConfigSymbol *)calloc(1, sizeof(NoisyConfigSymbol));
	if (newSymbol == NULL)
	{
		noisyConfigFatal(N, Emalloc);
	}

	newSymbol->identifier	= token->identifier;
	newSymbol->sourceInfo	= token->sourceInfo;
	newSymbol->scope	= scope;

	/*
	 *	NOTE:	An extant definition might not exist.
	 */
	newSymbol->definition	= noisyConfigSymbolTableSymbolForIdentifier(N, scope, token->identifier);

	/*
	 *	NOTE:	Caller sets (1) intconst/etc. fields, (2) type, based on context.
	 *		Caller sets the typesig based on the parsed typeexpr for defns.
	 */
	if (scope->firstSymbol == NULL)
	{
		scope->firstSymbol = newSymbol;
	}
	else
	{
		NoisyConfigSymbol *	p = scope->firstSymbol;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = newSymbol;
	}

	return newSymbol;
}


NoisyConfigSymbol *
noisyConfigSymbolTableSymbolForIdentifier(NoisyConfigState *  N, NoisyConfigScope *  scope, const char *  identifier)
{
	/*
	 *	Recursion falls out when we reach root which has nil parent
	 */
	if (scope == NULL)
	{
		return NULL;
	}

	/*
	 *	Search current and parent (not siblings or children)
	 */
	NoisyConfigSymbol *	p = scope->firstSymbol;
	while (p != NULL)
	{
		if (!strcmp(p->identifier, identifier))
		{
			return p;
		}
		p = p->next;
	}

	return noisyConfigSymbolTableSymbolForIdentifier(N, scope->parent, identifier);
}


NoisyConfigScope *
noisyConfigSymbolTableOpenScope(NoisyConfigState *  N, NoisyConfigScope *  scope, NoisyConfigIrNode *  subTree)
{
	NoisyConfigScope *	newScope = noisyConfigSymbolTableAllocScope(N);

	newScope->parent = scope;
	newScope->begin = subTree->sourceInfo;
	scope->firstChild = newScope;

	return newScope;
}


void
noisyConfigSymbolTableCloseScope(NoisyConfigState *  N, NoisyConfigScope *  scope, NoisyConfigIrNode *  subTree)
{
	scope->end = subTree->sourceInfo;
}
