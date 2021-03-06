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
    auto Pid::solve(double trueVal,double dtrueVal)->void{
        Pid::error_ - Pid::target_ - trueVal;
        Pid::integral_ += Pid::error_;
        Pid::result_ = Pid::error_ * Pid::P_ - (dtrueVal) * Pid::D_ +  Pid::integral_ * Pid::I_;
        Pid::pre_trueVal_ = trueVal;
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



    auto Kalman::solve()->void
    {
        //下一步的预测值
        double Axk_1 [s_status_];
        Size one(1);
        mult(s_status_,s_status_,1,A_,xk_1_,Axk_1);
        double Buk_1 [s_status_];
        mult(s_status_,s_control_,1,B_,uk_1_,Buk_1);
        double xk_[s_status_];
        add(s_status_,1,Axk_1,Buk_1,xk_);

        //预测值和真实值之间的协方差矩阵
        double APAT [s_status_*s_status_];
        amat(s_status_,s_status_,A_,Pk_1_,APAT);
        double Pk__ [s_status_*s_status_];
        add(s_status_,s_status_,APAT,Q_,Pk__);

        //卡尔曼增益
        double Kk;
        





    }

}