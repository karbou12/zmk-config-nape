# Nape firmware

`main`はNape Console正式版に対応した`nape-console.uf2`をビルドします。`console-beta`の変更は`main`へ統合済みです。`config/west.yml`で専用ZMK forkとドライバーのコミットを固定しています。

## ファームウェアを使う

[最新Release](https://github.com/menbou0202/zmk-config-nape/releases/latest)の「Assets」から`nape-console.uf2`をダウンロードしてください。ビルド済みファームウェアの利用にGitHubアカウントやForkは不要です。

- [ファームウェアの書き込み方法](https://github.com/menbou0202/Nape/blob/main/doc/build-guide.md)
- [Nape Consoleの使い方](https://github.com/menbou0202/nape-console/blob/main/HOW_TO_USE.md)
- [Nape Consoleを開く](https://menbou0202.github.io/nape-console/)

## 自分のForkでビルドする場合

1. GitHubにログインし、このリポジトリ右上の「Fork」から自分のアカウントへコピーします。
2. 自分のForkで「Actions」を開き、有効化の確認が表示されたらワークフローを有効にします。
3. `main`の`config/nape.keymap`などを編集し、コミット・pushするとビルドが始まります。
4. 変更せずにビルドする場合は、「Actions」→「Build ZMK firmware」→「Run workflow」で`main`を選びます。
5. 成功した実行結果の「Artifacts」から`firmware`のZIPをダウンロードし、展開して`nape-console.uf2`を取り出します。

以前からのForkを同期する場合、現在の`main`では従来版ではなくNape Console対応ファームウェアがビルドされる点に注意してください。

## 過去の利用者向け

旧ZMK向けの[`basic-driver`ブランチ](https://github.com/menbou0202/zmk-config-nape/tree/basic-driver)は、トラックボールの向きを実行時に切り替えるNape独自の処理を使わず、`inorichi/zmk-pmw3610-driver`を参照する保存版です。過去の利用者のため残していますが、新規利用には推奨しません。

別の旧ドライバーである[`menbou0202/zmk-pmw3610-driver`](https://github.com/menbou0202/zmk-pmw3610-driver)も過去の設定・forkの参照先として残しています。現在の`main`は[`zmk-pmw3610-driver-nape`](https://github.com/menbou0202/zmk-pmw3610-driver-nape)を使用します。

## Trackball Shift

本リポジトリはNapeをForkして、Trackball Shift機能を搭載したものです。

### `console/feature/trackball-shift` branch

Trackball Shift機能を搭載し、Nape Consoleに対応したbranchとなります。
Trackball Shift機能の概要については、私 (karbou12) がForkした`zmk-pmw3610-driver-nape`ドライバの[`console/feature/trackball-shift`branch](https://github.com/karbou12/zmk-pmw3610-driver-nape/tree/console/feature/trackball-shift)を参照してください。

### Trackball angle LED indication

Trackball Shift機能で角度を変更した場合、角度に対応した色でLEDを3回点滅させます。
角度と色の対応は`src/trackball_angle_rgb.c`にあります。

私 (karbou12) がForkした `zmk-rgbled-widget` の [`feature/color-indication-api`branch](https://github.com/karbou12/zmk-rgbled-widget/tree/feature/color-indication-api)を使用しています。
点灯・消灯の間隔は`CONFIG_RGBLED_WIDGET_LAYER_BLINK_MS`を使用します。
`CONFIG_RGBLED_WIDGET_SHOW_LAYER_COLORS`が有効な場合、点滅中にレイヤーが変わっても、点滅終了時にその時点で有効なレイヤー色へ戻ります。

本リポジトリでは`CONFIG_RGBLED_WIDGET_SHOW_LAYER_COLORS`を有効にし、以下の色を設定しています。

`boards/shields/nape/nape.conf`
```ini
# CONFIG_RGBLED_WIDGET_SHOW_LAYER_CHANGE=y
CONFIG_RGBLED_WIDGET_SHOW_LAYER_COLORS=y

CONFIG_RGBLED_WIDGET_LAYER_0_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_1_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_2_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_3_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_4_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_5_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_6_COLOR=0
CONFIG_RGBLED_WIDGET_LAYER_7_COLOR=0
 # bt sel: white
CONFIG_RGBLED_WIDGET_LAYER_8_COLOR=7
# bt clr: red
CONFIG_RGBLED_WIDGET_LAYER_9_COLOR=1
# scroll: yellow
CONFIG_RGBLED_WIDGET_LAYER_10_COLOR=3
# orientation: blue
CONFIG_RGBLED_WIDGET_LAYER_11_COLOR=4
# trackball shift: green
CONFIG_RGBLED_WIDGET_LAYER_12_COLOR=2
```

色の番号は以下の割り振りとなります。

`zmk-rgbled-widget/Kconfig`
```ini
# Color definitions to use with color settings
COLOR_BLACK   := 0
COLOR_RED     := 1
COLOR_GREEN   := 2
COLOR_YELLOW  := 3
COLOR_BLUE    := 4
COLOR_MAGENTA := 5
COLOR_CYAN    := 6
COLOR_WHITE   := 7
```
