/*
	Authored 2016. Jonathan Lim.

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


Dimension *	newtonDimensionTableAddDimensionForToken(State *  N, Scope *  scope, Token *  nameToken, Token * abbrevToken);
Dimension *	newtonDimensionTableDimensionForName(State *  N, Scope *  scope, const char *  identifier);
Physics *	newtonInitPhysics(State * N, Scope * scope, Token * token);
Physics *	newtonPhysicsTableAddPhysicsForToken(State *  N, Scope *  scope, struct Token *  token);
Physics *	newtonPhysicsTablePhysicsForIdentifier(State *  N, Scope *  scope, const char *  identifier);
Physics *	newtonPhysicsTablePhysicsForIdentifierAndSubindex(State *  N, Scope *  scope, const char *  identifier, int subindex);
Physics *	newtonPhysicsTablePhysicsForDimensionAlias(State *  N, Scope *  scope, const char * dimensionAliasIdentifier);
Physics *	newtonPhysicsTablePhysicsForDimensionAliasAbbreviation(State *  N, Scope *  scope, const char * dimensionAliasAbbreviation);
Physics *	newtonPhysicsTableAddPhysics(State *  N, Scope *  scope);
Physics *	newtonPhysicsTableCopyAndAddPhysics(State *  N, Scope *  scope, Physics *  source);
Physics *	deepCopyPhysicsNode(Physics *  node);
Physics *	shallowCopyPhysicsNode(Physics *  node);
Physics *	getTailPhysics(Physics *  list);
IntegralList *	getTailIntegralList(IntegralList *  list);
int		countNumberTime(Dimension *  head);
void		newtonPhysicsIncrementExponent(State *  N, Physics *  source, Dimension *  added);
void		newtonPhysicsAddExponents(State *  N, Physics *  left, Physics *  right);
void		newtonPhysicsAddExponentsRecursively(State *  N, Physics *  baseNode, IrNode * treeRoot);
void		newtonPhysicsSubtractExponents(State *  N, Physics *  left, Physics *  right);
void		newtonPhysicsMultiplyExponents(State *  N, Physics *  source, double multiplier);
void		newtonAddInvariant(State *  N, Invariant *  invariant);
bool		areTwoPhysicsEquivalent(State *  N, Physics *  left, Physics *  right);
