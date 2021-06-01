#ifndef CONTROLBOX
#define CONTROLBOX
#include "Matrix.hpp"

namespace ControlBox{
    class Pid{
        public:
            auto init()->void;
            auto setParams(double P, double I, double D)->void ;
            auto setParams(double P, double I, double D, double target)->void ;
            auto setP(double P)->void;
            auto setI(double I)->void;
            auto setD(double D)->void;
            auto setTarget(double target)->int;
            auto solve(double trueVal)->void;
            auto solve(double trueVal, double dtrueVal)->void;
            auto getResult()->auto;
            auto resetIntegral()->void;

        private:

            double P_;
            double I_;
            double D_;
            double error_;
            double target_;
            double pre_trueVal_;
            double integral_;
            double result_;        
    };

    class Kalman{
        public:
            auto init()->void;
            auto setParams()->void;
            auto setQ(double Q)->void;
            auto setP(double P)->void;
            auto solve()->void;
            auto getResult()->auto;
            

        private:
            double* A_;
            double* B_;
            double* Q_;
            double* Pk_;
            double* R_;
            double* K_;
            double* H_;
            Size s_status_;
            

    };
}


#endif