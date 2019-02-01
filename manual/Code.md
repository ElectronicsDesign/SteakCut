# SteakCut ソースコードマニュアル
## 開発環境
- Visual Studio 2015 Community
- Visual Studio 2017 Enterprise
## 使用ライブラリ
- DX Library (Copyright (C) 2001-2019 Takumi Yamada.)
## 今回作成したコード及び機能について
- src/AreaCheck.cpp
  - ステーキを切る動作を実行するためのファイル
- src/AreaCheck.h
  - AreaCheck.cppで定義した関数を他ファイルで呼び出すためのヘッダーファイル
- src/Debug.cpp
  - デバッグ用関数のセット
- src/Debug.h
  - Debug.cppで定義した関数を他ファイルで呼び出すためのヘッダーファイル
- src/GameMain.cpp
  - 実際にプレイする画面を動かすための関数ファイル
- src/GameMain.h
  - GameMain.cppで定義した関数を他ファイルで呼び出すためのヘッダーファイル
- src/Main.cpp
  - ソフトウェアの起動を行うにあたりアプリケーションの初期化等を実行するファイル
- src/MenuArea.cpp
  - メニュー画面を表示、動作させるためのファイル
- src/MenuArea.h
  - MenuArea.cppで定義した関数を他ファイルで呼び出すためのヘッダーファイル
- src/api.cpp
  - メモリ改ざん検出プログラム用API
- src/api.h
  - API呼び出し用ヘッダー
## コンパイルしてアプリケーションを起動するまで
1. EleSteak.slnファイルを開いてください。Visual Studio 2010 (Version 10.0.30319.1)以降で開けます。  
起動時にプロジェクトの再ターゲットが表示される場合がありますが、キャンセルをクリックしてダイアログを閉じてください。  
2. ソリューション構成をRelease、ソリューションプラットフォームをx64からx86に変更してください。  
(これはSpidarMouse.dllが64ビットに対応していないためです。)  
![1](https://github.com/tmorio/SteakCut/blob/master/manual/img/Code1.png?raw=true "1") 
3. ビルドから「ソリューションのビルド」を選択してください。  
![2](https://github.com/tmorio/SteakCut/blob/master/manual/img/Code2.png?raw=true "2") 
4. ビルドが完了すると、.slnファイルがあるフォルダに、「Release」というフォルダが生成されます。
![3](https://github.com/tmorio/SteakCut/blob/master/manual/img/Code3.png?raw=true "3") 
5. フォルダが生成されたら、SpidarMouse.dllをReleaseフォルダの中にコピーして下さい。  
![4](https://github.com/tmorio/SteakCut/blob/master/manual/img/Code4.png?raw=true "4") 
6. コピー後、Releaseフォルダの中にあるEleSteak.exeを起動すると、アプリケーションが起動します。
## よくある質問
- Q. ソリューションのビルド時、「C4819 ファイルは、現在のコード ページ (932) で表示できない文字を含んでいます。データの損失を防ぐために、ファイルを Unicode 形式で保存してください。」とエラーが出る。
  - A. 環境やダウンロード時により発生することがある問題です。解決方法は、エラーが出たファイルのソースコードをctrl + Aで全選択、コピーを行って、一度該当するファイルを削除します。その後、同じファイル名でファイルを作成しペーストして下さい。
