# include <Siv3D.hpp> // Siv3D v0.6.16

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.9 });

	// 統一初期化構文↓
	const Texture playerTexture{ U"🐈‍⬛"_emoji };

	const Texture backGroundTexture{ U"🌳"_emoji };

	const Texture floor{ U"🧱"_emoji };

	// プレイヤーの移動スピード | Player's movement speed
	constexpr double speed = 400.0;

	Vec2 playerPos{400.0, 540.0};

	constexpr double gravity = 1500.0;
	double jumpTime = 0.0;
	constexpr double jumpPower = 1000.0;

	constexpr double groundHeight = 540.0;

	bool isPlayerJumping = false;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	constexpr double leftWall = 60.0;
	constexpr double rightWall = 1740.0;

	constexpr Vec2 center{400.0, 200.0};

	Camera2D camera{center, 1.0, CameraControl::Default};

	while (System::Update())
	{

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed() || KeyA.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPos.x = Max((playerPos.x - speed * Scene::DeltaTime()), leftWall);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed() || KeyD.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPos.x = Min((playerPos.x + speed * Scene::DeltaTime()), rightWall);
			isPlayerFacingRight = true;
		}

		if (KeySpace.pressed() || isPlayerJumping)
		{
			double y = 0.5*gravity*jumpTime*jumpTime - jumpPower*jumpTime + groundHeight;
			playerPos.y = y;
			isPlayerJumping = true;

			if (playerPos.y >= groundHeight)
			{
				isPlayerJumping = false;
				jumpTime = 0.0;
			}
			jumpTime = jumpTime + Scene::DeltaTime();
		}

		camera.jumpTo(playerPos, 1);
		camera.update();
		const auto tr = camera.createTransformer();

		// 背景を描く
		for (int32 y = 0; y < 4; ++y)
		{
			for (int32 x = 0; x < 100; ++x)
			{
				backGroundTexture.drawAt(x * 150, y * 150);
			}
		}

		// 床を描く
		for (int32 y = 0; y < 5; ++y)
		{
			for (int32 x = 0; x < 100; ++x)
			{
				floor.drawAt(x * 120, 630 + y * 120);
			}
		}


		// プレイヤーを描く | Draw the player
		playerTexture.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPos.x, playerPos.y);


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
