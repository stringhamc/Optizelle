// In this example, we setup and minimize the Rosenbrock function.

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include "optizelle/optizelle.h"
#include "optizelle/vspaces.h"
#include "optizelle/json.h"

//---Objective0---
// Squares its input
template <typename Real>
Real sq(Real x){
    return x*x; 
}

// Define the Rosenbrock function where
// 
// f(x,y)=(1-x)^2+100(y-x^2)^2
//
struct Rosenbrock
    : public Optizelle::ScalarValuedFunction <double,Optizelle::Rm>
{
    typedef Optizelle::Rm <double> X;

    // Evaluation of the Rosenbrock function
    double eval(const X::Vector& x) const {
        return sq(1.-x[0])+100.*sq(x[1]-sq(x[0]));
    }

    // Gradient
    void grad(
        const X::Vector& x,
        X::Vector& grad
    ) const {
        grad[0]=-400.*x[0]*(x[1]-sq(x[0]))-2.*(1.-x[0]);
        grad[1]=200.*(x[1]-sq(x[0]));
    }

    // Hessian-vector product
    void hessvec(
        const X::Vector& x,
        const X::Vector& dx,
        X::Vector& H_dx
    ) const {
    	H_dx[0]=(1200.*sq(x[0])-400.*x[1]+2)*dx[0]-400.*x[0]*dx[1];
        H_dx[1]=-400.*x[0]*dx[0]+200.*dx[1];
    }
};
//---Objective1---

//---Preconditioner0---
// Define a perfect preconditioner for the Hessian
struct RosenHInv :
    public Optizelle::Operator <double,Optizelle::Rm,Optizelle::Rm>
{
public:
    typedef Optizelle::Rm <double> X;
    typedef X::Vector X_Vector;
private:
    X_Vector& x;
public:
    RosenHInv(X::Vector& x_) : x(x_) {}
    void eval(const X_Vector& dx,X_Vector &result) const {
        double one_over_det=1./(80000.*sq(x[0])-80000.*x[1]+400.);
        result[0]=one_over_det*(200.*dx[0]+400.*x[0]*dx[1]);
        result[1]=one_over_det*
            (400.*x[0]*dx[0]+(1200.*x[0]*x[0]-400.*x[1]+2.)*dx[1]);
    }
};
//---Preconditioner1---

int main(int argc,char* argv[]){
    // Read in the name for the input file
    if(argc!=2) {
        std::cerr << "rosenbrock <parameters>" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string fname(argv[1]);

    //---State0---
    // Generate an initial guess for Rosenbrock
    std::vector <double> x(2);
    x[0]=-1.2; x[1]=1.;

    // Create an unconstrained state based on this vector
    Optizelle::Unconstrained <double,Optizelle::Rm>::State::t state(x);
    //---State1---

    //---Parameters0---
    // Read the parameters from file
    Optizelle::json::Unconstrained <double,Optizelle::Rm>
        ::read(Optizelle::Messaging(),fname,state);
    //---Parameters1---

    //---Functions0---
    // Create the bundle of functions 
    Optizelle::Unconstrained <double,Optizelle::Rm>::Functions::t fns;
    fns.f.reset(new Rosenbrock);
    fns.PH.reset(new RosenHInv(state.x));
    //---Functions1---

    //---Solver0---
    // Solve the optimization problem
    Optizelle::Unconstrained <double,Optizelle::Rm>::Algorithms
        ::getMin(Optizelle::Messaging(),fns,state);
    //---Solver1---

    //---Extract0---
    // Print out the reason for convergence
    std::cout << "The algorithm converged due to: " <<
        Optizelle::StoppingCondition::to_string(state.opt_stop) <<
        std::endl;

    // Print out the final answer
    std::cout << "The optimal point is: (" << state.x[0] << ','
        << state.x[1] << ')' << std::endl;
    //---Extract1---

    // Write out the final answer to file
    Optizelle::json::Unconstrained <double,Optizelle::Rm>::write_restart(
        Optizelle::Messaging(),"solution.json",state);

    // Successful termination
    return EXIT_SUCCESS;
}
