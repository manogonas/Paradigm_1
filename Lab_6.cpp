#include <iostream>
#include <cassert>
using namespace std;

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression {
	virtual ~Expression() { }
	virtual double evaluate() const = 0;
	virtual Expression* transform(Transformer* tr) const = 0;
};

struct Transformer { //pattern Visitor
	virtual ~Transformer() { }
	virtual Expression* transformNumber(Number const*) = 0;
	virtual Expression* transformBinaryOperation(BinaryOperation const*) = 0;
	virtual Expression* transformFunctionCall(FunctionCall const*) = 0;
	virtual Expression* transformVariable(Variable const*) = 0;
};

struct Number : Expression {
	Number(double value);
	double value() const;
	double evaluate() const;
	Expression* transform(Transformer* tr) const;
	private:
		double value_;
};

struct BinaryOperation : Expression {
	enum {
		PLUS = '+',
		MINUS = '-',
		DIV = '/',
		MUL = '*'
	};
	BinaryOperation(Expression const* left, int op, Expression const* right);
	~BinaryOperation();
	double evaluate() const;
	Expression* transform(Transformer* tr) const;
	Expression const* left() const;
	Expression const* right() const;
	int operation() const;
	private:
		Expression const* left_;
		Expression const* right_;
		int op_;
};

struct FunctionCall : Expression {
	FunctionCall(string const& name, Expression const* arg);
	~FunctionCall();
	double evaluate() const;
	Expression* transform(Transformer* tr) const;
	string const& name() const;
	Expression const* arg() const;
	private:
		string const name_;
		Expression const* arg_;
};

struct Variable : Expression {
	Variable(string const name);
	string const& name() const;
	double evaluate() const;
	Expression* transform(Transformer* tr) const;
	private:
		string const name_;
};

/**
 * реализуйте все необходимые методы класса
 * вы можете определять любые вспомогательные
 * методы, если хотите
 */

struct CopySyntaxTree : Transformer {
	Expression* transformNumber(Number const* number) {
		// ваш код
	}
	Expression* transformBinaryOperation(BinaryOperation const* binop) {
		// ваш код
	}
	Expression* transformFunctionCall(FunctionCall const* fcall) {
		// ваш код
	}
	Expression* transformVariable(Variable const* var) {
		// ваш код
	}
};

int main() {
	Number* n32 = new Number(32.0);
	Number* n16 = new Number(16.0);
	BinaryOperation* minus = new BinaryOperation(n32, BinaryOperation::MINUS, n16);
	FunctionCall* callSqrt = new FunctionCall("sqrt", minus);
	Variable* var = new Variable("var");
	BinaryOperation* mult = new BinaryOperation(var, BinaryOperation::MUL, callSqrt);
	FunctionCall* callAbs = new FunctionCall("abs", mult);
	CopySyntaxTree CST;
	Expression* newExpr = callAbs->transform(&CST);
};