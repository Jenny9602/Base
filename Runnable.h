#ifndef HEADER_RUNNABLE
#define HEADER_RUNNABLE

#include <thread>

class CRunnable
{
public:
	CRunnable() : _stop(false) {}
	virtual ~CRunnable() {}

	//线程基本操作
	virtual void Start() {
		_stop = false;
		if (!_pthread) {
			_pthread = std::shared_ptr<std::thread>(new std::thread(std::bind(&CRunnable::Run, this)));
		}
	}
	virtual void Stop() {
		_stop = true;
	}
	virtual void Join() {
		if (_pthread) {
			_pthread->join();
		}
	}

	//线程主逻辑
	virtual void Run() = 0;

	bool GetStop() {
		return _stop;
	}

	static void Sleep(int interval) {
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
	}

protected:
	CRunnable(const CRunnable&) = delete;
	CRunnable& operator=(const CRunnable&) = delete;

protected:
	bool							_stop;
	std::shared_ptr<std::thread>	_pthread;
};
#endif