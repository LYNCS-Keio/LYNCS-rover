#pragma once
namespace lyncs
{
template <typename T>
class LowPass
{
  private:
	T data_;
	T last_data_;
  public:
	LowPass();
	~LowPass();
	InputData(const T kInput);
	const T GetData() const;
};

template <typename T>
LowPass<T>::InputDataconst T kInput){
	data_=
}

template <typename T>
LowPass<T>::LowPass()
{
}

template <typename T>
LowPass<T>::~LowPass()
{
}

} // namespace lyncs