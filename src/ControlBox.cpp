#include "include/ControlBox.hpp"

namespace ControlBox{
    auto Pid::init()->void{
        Pid::error_ = 0;
        Pid::I_ = 0;
        Pid::P_ = 0;
        Pid::D_ = 0;
        Pid::target_ = 0;
        Pid::integral_ = 0;
        Pid::pre_trueVal_ = 0;
        
    }
    auto Pid::solve(double trueVal,double dtrueVal)->auto{

    }
    auto Pid::setP(double P)->void{Pid::P_ = P;}
    auto Pid::setI(double I)->void{Pid::I_ = I;}
    auto Pid::setD(double D)->void{Pid::D_ = D;}
    auto Pid::setParams(double P, double I, double D)->void{Pid::P_ = P;Pid::I_ = I;Pid::D_ = D;}
    auto Pid::setParams(double P, double I, double D, double target)->void{Pid::P_ = P;Pid::I_ = I;Pid::D_ = D;Pid::target_ = target;}
    auto Pid::solve(double trueVal)->void{
        Pid::error_ = Pid::target_ - trueVal;
        Pid::integral_ += Pid::error_;
        Pid::result_ = Pid::error_ * Pid::P_ - (trueVal - Pid::pre_trueVal_)*Pid::D_ +  Pid::integral_ * Pid::I_;
        Pid::pre_trueVal_ = trueVal;
    }
    auto Pid::getResult()->auto{return Pid::result_;}

}