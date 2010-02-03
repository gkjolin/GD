#ifndef EXPRESSIONINSTRUCTION_H
#define EXPRESSIONINSTRUCTION_H

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
class GDExpression;
class ExpressionInstruction;
class Object;
class ObjectsConcerned;
class RuntimeScene;

typedef std::vector < boost::shared_ptr<Object> > ObjList;
typedef boost::shared_ptr<Object> ObjSPtr;

class GD_API ExpressionInstruction
{
    typedef double (*PtrFunction)( const RuntimeScene * scene, ObjectsConcerned * objectsConcerned, ObjSPtr obj1, ObjSPtr obj2, const ExpressionInstruction & exprInstruction);
    typedef double (Object::*PtrObjectFunction)( const RuntimeScene * scene, ObjectsConcerned * objectsConcerned, ObjSPtr obj1, ObjSPtr obj2, const ExpressionInstruction & exprInstruction);

    public:
        ExpressionInstruction();
        virtual ~ExpressionInstruction();

        PtrFunction                 function;
        PtrObjectFunction           objectFunction;
        std::vector<GDExpression>   parameters;

    protected:
    private:
};

#endif // EXPRESSIONINSTRUCTION_H