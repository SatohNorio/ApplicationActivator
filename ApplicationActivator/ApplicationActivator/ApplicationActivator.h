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

		// ref classのデストラクタにはvirtual宣言は不要(C++/CLIの仕様)
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

		// 同じ実行ファイルが既に起動していればウィンドウをアクティブにする
		// アクティブにできなければ（起動していなければ）falseを返す
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

		// 指定した名前のプロセスをアクティブにする
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
