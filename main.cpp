#include "InputHandler.h"
#include "Player.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2C_08_サカモトイクミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	InputHandler* inputHandler = new InputHandler();
	inputHandler->AssignMoveLeftCommand2PressKeyA();
	inputHandler->AssignMoveRightCommand2PressKeyD();

	ICommand* iCommand = nullptr;
	Player* player = new Player();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		iCommand = inputHandler->HandleInput();

		if (iCommand) {
			iCommand->Exec(*player);
		}

		player->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();

		Novice::ScreenPrintf(0, 0, "A : LEFT MOVE");
		Novice::ScreenPrintf(0, 20, "D : RIGHT MOVE");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}