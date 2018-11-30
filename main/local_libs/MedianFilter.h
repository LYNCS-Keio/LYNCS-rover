#pragma once
namespace lyncs
{

template <typename T, unsigned int N>
class MedianFilter
{
  private:
	void bubbleSort(T list[N]);
	T Median(T list[N]);
	T data_array_[N];

  public:
	MedianFilter();
	~MedianFilter();
	void InputData(T newdata);
	T GetData() const;
};

template <typename T, unsigned int N>
MedianFilter<T, N>::MedianFilter(/* args */)
{
}

template <typename T, unsigned int N>
MedianFilter<T, N>::~MedianFilter()
{
}

template <typename T, unsigned int N>
void MedianFilter<T, N>::bubbleSort(T list[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = N - 1; j > i; j--)
		{
			if (list[j] < list[j - 1])
			{
				unsigned long temp = list[j];
				list[j] = list[j - 1];
				list[j - 1] = temp;
			}
		}
	}
}

template <typename T, unsigned int N>
void MedianFilter<T, N>::InputData(T newdata)
{
	for (int i = 0; i < N - 1; i++)
	{
		data_array_[i] = data_array_[i + 1];
	}
	data_array_[N - 1] = newdata;
}

template <typename T, unsigned int N>
T MedianFilter<T, N>::GetData() const
{
	T sorted[N];
	for (int i = 0; i < N; i++)
	{
		sorted[i] = data_array_[i];
	}
	this->bubbleSort(sorted);
	return (sorted[N/ 2 - 1] + sorted[N/ 2]) / 2;
}

} // namespace lyncs