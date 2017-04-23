#pragma once

#define SINGELTON_FREND_CLASS_REGISTER(T) friend class CSingleton<T>

template<class T>
class CSingleton
{
public:
	static bool CreateInstance(void)
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new T;
		}
		return m_pInstance != NULL;
	}
	static T * Instance(void)
	{
		return m_pInstance;
	}
protected:
	CSingleton(void){}
	virtual ~CSingleton(void){}
private:
	static T * m_pInstance;
};

template<class T>
T * CSingleton<T>::m_pInstance = nullptr;
