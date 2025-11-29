# include <Siv3D.hpp> // Siv3D v0.6.16

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.9 });

	// 統一初期化構文↓
	const Texture emoji{ U"🐈‍⬛"_emoji };

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 400.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;
	double playerPosY = 540;

	constexpr double gravity = 1500;
	double jumptime = 0;
	constexpr double v0 = 1000;

	constexpr double ground = 540;

	bool isPlayerJumping = false;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	constexpr double leftWall = 60;
	constexpr double rightWall = 740;

	while (System::Update())
	{

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed() || KeyA.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), leftWall);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed() || KeyD.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), rightWall);
			isPlayerFacingRight = true;
		}

		if (KeySpace.pressed() || isPlayerJumping)
		{
			double y = 0.5*gravity*jumptime*jumptime - v0*jumptime + ground;
			playerPosY = y;
			isPlayerJumping = true;

			if (playerPosY >= ground)
			{
				isPlayerJumping = false;
				jumptime = 0;
			}
			jumptime = jumptime + Scene::DeltaTime();
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, playerPosY);
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
