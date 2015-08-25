========================================================================
    DYNAMIC LINK LIBRARY : ApplicationActivator Project Overview
========================================================================

AppWizard has created this ApplicationActivator DLL for you.  

This file contains a summary of what you will find in each of the files that
make up your ApplicationActivator application.

ApplicationActivator.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ApplicationActivator.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ApplicationActivator.cpp
    This is the main DLL source file.

ApplicationActivator.h
    This file contains a class declaration.

AssemblyInfo.cpp
    Contains custom attributes for modifying assembly metadata.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

■GitHubのリポジトリについて
  リポジトリの容量が大きくなるためApplicationActivator.sdfはリポジトリから除外しました。
  それにより、コンパイルするために以下の設定を行ってください。
  １．依存ファイルのリンク
      プロジェクトのプロパティ→[リンカー]→[入力]→[追加の依存ファイル]
      に「%(AdditionalDependencies)」を設定する。
      これは、プルダウンから[親またはプロジェクトの既定値を継承]を選んでも同じです。
  ２．ソリューションプラットフォームの変更
      ソリューションプラットフォームを[x64]（または[x86]）に変更します。
      Any CPUはC++が対応していないため実行時エラーになります。
  ３．スタートアッププロジェクトの変更
      スタートアッププロジェクトをApplicationActivatorTesterに変更する。
