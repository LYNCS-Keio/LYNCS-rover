#pragma once
namespace lyncs
{
 class PIDController
{
  private:
	const double kProportionGain_;
	const double kIntegralGain_;
	const double kDifferentialGain_;
 	double integral_;
	double prev_error_;
	double manipulative_variable_;
 	PIDController();
  public:
	PIDController(const double kProportionGain, const double kIntegralGain, const double kDifferentialGain);
	~PIDController();
	void InputPID(double data, double goal, double dt);
	const double GetPID() const;
};
 
 } // namespace lyncs 