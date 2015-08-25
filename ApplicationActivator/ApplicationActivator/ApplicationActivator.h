// ApplicationActivator.h

#pragma once

using namespace System;

namespace Ns {

	public ref class ApplicationActivator
	{
		typedef cli::array<Diagnostics::Process^, 1> ProcessArray;

	public:

		ApplicationActivator() : FMyProcess(Diagnostics::Process::GetCurrentProcess())
		{
			Diagnostics::Process ^p = this->MyProcess;
			String ^s = p->ProcessName;
			this->Mutex = gcnew Threading::Mutex(false, s);
		}

		// ref class�̃f�X�g���N�^�ɂ�virtual�錾�͕s�v(C++/CLI�̎d�l)
		~ApplicationActivator()
		{
			this->!ApplicationActivator();
		}

		!ApplicationActivator()
		{
			Threading::Mutex ^m = this->Mutex;
			if (m != nullptr)
			{
				GC::KeepAlive(m);
				m->Close();
				this->Mutex = nullptr;
			}
		}

		// �������s�t�@�C�������ɋN�����Ă���΃E�B���h�E���A�N�e�B�u�ɂ���
		// �A�N�e�B�u�ɂł��Ȃ���΁i�N�����Ă��Ȃ���΁jfalse��Ԃ�
		bool Activate()
		{
			bool b = false;
			if (!this->Mutex->WaitOne(0, false))
			{
				Diagnostics::Process ^myProcess = this->MyProcess;

				ProcessArray ^hProcess = Diagnostics::Process::GetProcessesByName(myProcess->ProcessName);
				for each (Diagnostics::Process ^p in hProcess)
				{
					b = (p->Id != myProcess->Id);
					if (b)
					{
						SetForegroundWindow((HWND)p->MainWindowHandle.ToPointer());
						break;
					}
				}
			}
			return b;
		}

		// �w�肵�����O�̃v���Z�X���A�N�e�B�u�ɂ���
		static bool ActivateWindow(String ^iProcessName)
		{
			bool b = false;
			ProcessArray ^hProcess = Diagnostics::Process::GetProcessesByName(iProcessName);
			for each (Diagnostics::Process ^p in hProcess)
			{
				SetForegroundWindow((HWND)p->MainWindowHandle.ToPointer());
				b = true;
				break;
			}
			return b;
		}

	protected:
		property Threading::Mutex ^Mutex;
		property Diagnostics::Process ^MyProcess
		{
			protected: Diagnostics::Process ^get()
			{
				return FMyProcess;
			}
		}
	private:
		Diagnostics::Process ^FMyProcess;
	};
}
