# MCC Git-C 言語講座 2

今回は Git を使って C言語 でリバーシプログラムを作ります。GIt が長くなったのでリバーシだけこっちにしました。

## リポジトリのクローン

まずこのリポジトリをクローンしましょう。

## WSL で開く(Mac の人はやらなくていいです)

Ctrl + P (Mac はたぶん Command + P) でコマンドパレットを開きます。

`> wsl` と打って出てきた `WSL でフォルダーをもう一度開く...` を選択してください。

![openwsl](./resources/openwsl.png)

WSL でウィンドウを開いたら VS Code の拡張機能の Git Graoh と Git History を WSL 用に入れてください。入れ直さないといけないみたいです。

![gitinstall](./resources/gitinstall.png)

最初から WSL でやれよ！とか言わないでください。 Windows でも Git の環境作ったほうが将来的に便利ですよ！！！

* メアドと名前設定

ここでも Github のダミーメアドとユーザーネームを使います。WSL でもメアドと名前のコマンドは同じです。

```
git config --global user.email メールアドレス
```
```
git config --global user.name ユーザー名
```