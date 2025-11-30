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



	constexpr double gravity = 1500.0;
	double jumpTime = 0.0;
	constexpr double jumpPower = 1000.0;

	constexpr double groundHeight = 540.0;

	bool isPlayerJumping = false;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	constexpr double leftWall = 60.0;
	constexpr double rightWall = 3000.0;

	constexpr double floorTextureSize = 120.0;
	constexpr double floorStartHeight = 630.0;
	constexpr double backgroundTextureSize = 150.0;

	double windowWidth = Window::DefaultClientSize.x;
	double windowHeight = Window::DefaultClientSize.y;

	Grid<int32> map = {
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	};

	Vec2 playerPos{windowWidth / 2.0, 540.0};

	Camera2D camera{ Vec2{ windowWidth / 2.0, 500}, 1.0, CameraControl::Default};

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

		if (KeySpace.pressed())
		{
			isPlayerJumping = true;
		}

		if (isPlayerJumping)
		{
			// ジャンプ処理、今回は鉛直投げ上げの式を採用
			// 参考文献
			// https://qiita.com/odanny/items/297f32a334c41410cc5d
			double y = 0.5*gravity*jumpTime*jumpTime - jumpPower*jumpTime + groundHeight;
			playerPos.y = y;


			if (playerPos.y > groundHeight)
			{
				isPlayerJumping = false;
				jumpTime = 0.0;
				//沈み込みを避けるために地面位置を代入
				playerPos.y = groundHeight;
			}
			else
			{
				jumpTime = jumpTime + Scene::DeltaTime();
			}


		}

		//カメラはプレイヤーよりちょっと上に固定
		Vec2 cameraPos{ playerPos.x, playerPos.y - 200.0 };

		camera.jumpTo(cameraPos, 1.0);
		camera.update();
		const auto tr = camera.createTransformer();

		// 背景を描く
		for (int32 y = 0; y < 4; ++y)
		{
			for (int32 x = 0; x < 100; ++x)
			{
				backGroundTexture.drawAt(x * backgroundTextureSize, y * backgroundTextureSize);
			}
		}

		// 床を描く
		for (int32 y = 0; y < map.height() ; ++y)
		{
			for (int32 x = 0; x < map.width() ; ++x)
			{
				if (map[y][x] == 1)
				{
					floor.drawAt(x * floorTextureSize, y * floorTextureSize);
				}

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
