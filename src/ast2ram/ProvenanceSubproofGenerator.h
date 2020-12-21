/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018 The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file ProvenanceSubproofGenerator.h
 *
 ***********************************************************************/

#pragma once

#include "ast2ram/ClauseTranslator.h"

namespace souffle::ast {
class Clause;
}

namespace souffle::ram {
class Condition;
class Operation;
class Statement;
}  // namespace souffle::ram

namespace souffle::ast2ram {

class TranslatorContext;

class ProvenanceSubproofGenerator : public ClauseTranslator {
public:
    ProvenanceSubproofGenerator(const TranslatorContext& context, SymbolTable& symbolTable)
            : ClauseTranslator(context, symbolTable) {}

    static Own<ram::Statement> generateSubproof(const TranslatorContext& context, SymbolTable& symbolTable,
            const ast::Clause& clause, int version = 0);

protected:
    Own<ram::Statement> createRamFactQuery(const ast::Clause& clause) const override;
    Own<ram::Statement> createRamRuleQuery(const ast::Clause& clause) override;
    Own<ram::Operation> addNegatedAtom(Own<ram::Operation> op, const ast::Atom* atom) const override;
    Own<ram::Operation> generateReturnInstantiatedValues(const ast::Clause& clause) const;
    Own<ram::Operation> addBodyLiteralConstraints(
            const ast::Clause& clause, Own<ram::Operation> op) const override;
};
}  // namespace souffle::ast2ram