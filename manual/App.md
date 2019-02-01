# SteakCut アプリケーションマニュアル
## 推奨環境
- Windows Vista以上
- メモリ128MB以上
- ディスクの空きが10MB以上
## コンパイル済みアプリケーションの入手先
[Releases](https://github.com/tmorio/SteakCut/releases)からダウンロードできます。  
最新版(v1.9)は[https://github.com/tmorio/SteakCut/releases/download/Ver1.9/Ver19.zip](https://github.com/tmorio/SteakCut/releases/download/Ver1.9/Ver19.zip)からダウンロードできます。
## 起動方法、使い方
1. ダウンロードしたファイルを展開すると、「EleSteak.exe」という実行ファイルがあるので、ダブルクリックで起動します。  
USBデバイスは起動前に接続しても大丈夫です。  
2. ソフトウェアが起動すると、次のタイトル画面が表示されます。  
![1](https://github.com/tmorio/SteakCut/blob/master/manual/img/Title1.png?raw=true "1")   
尚、USBデバイスとの接続が完了していると、左上に「接続済み」と表示されます。  
![2](https://github.com/tmorio/SteakCut/blob/master/manual/img/Title2.png?raw=true "2") 

<br/>

メニュー操作は矢印キー(↑, ↓, ←, →)、選択はEnterキーを使用します。  
ここからは各機能別に使い方をご説明致します。  

### スタート
1. スタート画面を選択すると、次の画像のように、マウスの初期位置設定画面となります。  
中心になる緑色の点を左クリックすると次に進めます。  
![1](https://github.com/tmorio/SteakCut/blob/master/manual/img/Start1.png?raw=true "1") 
2. ステーキの画像が表示されたら、実際に切ることができます。 
![2](https://github.com/tmorio/SteakCut/blob/master/manual/img/Start2.png?raw=true "2") 

最初に左クリックをして、「切ってみよう！」という表示がある場所で、上下にマウスを動かします。  
動かしていくと、ステーキが切れていきます。  
![3](https://github.com/tmorio/SteakCut/blob/master/manual/img/Start3.png?raw=true "3") 

3. ステーキが一定の位置になる画面のメッセージが表示されて、特定の部分が切れなくなります。  
この場合はRキーを押すことでリセットできます。  
Mキーを押すと、タイトル画面に戻れます。  
![4](https://github.com/tmorio/SteakCut/blob/master/manual/img/Start4.png?raw=true "4") 

### デバイス管理
デバイス管理では、USBデバイスとの接続、切断、各モーターの動作確認を行うことができます。  
画像はUSBデバイスが未接続時の表示です。  
![1](https://github.com/tmorio/SteakCut/blob/master/manual/img/Title3.png?raw=true "1") 
USBデバイスを接続した状態で、「USBデバイスと接続」を選択すると、接続確認が行われ通信可能な状態にします。  
接続成功すると以下の画面になります。  
![2](https://github.com/tmorio/SteakCut/blob/master/manual/img/Title4.png?raw=true "2") 

<br />

### うまく接続できない場合
- 以下の3点をご確認ください。
  - PICのドライバーが正常にインストールできているか。
  - ケーブルが内部で断線していないか(別のケーブルをお試し下さい。)
  - PICが壊れていないか。
