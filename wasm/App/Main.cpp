
# include <Siv3D.hpp> // OpenSiv3D v0.4.0
#include<emscripten.h>
#include <SDL2/SDL.h>

template<class F>
struct AAA{
	static void impl(void*arg){
		if(	System::Update()){
			auto fp = static_cast<F*>(arg);
			(*fp)();
		}else{
			emscripten_cancel_main_loop();
		}
	}
	static void apply(F f){
		emscripten_set_main_loop_arg(impl,&f,-1,1);
	}
};

template<class F>
void MainLoop(F f){
	AAA<F>::apply(f);
}

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	
	// 大きさ 60 のフォントを用意
	const Font font(60);
	
	// 猫のテクスチャを用意
	//const Texture cat(Emoji(U"🐈")); // なんか動かん
	const Texture cat(U"assets/gohoubi.png");
	
	// 猫の座標
	Vec2 catPos(640, 450);
	MainLoop([&]{
		cat.resized({64,32}).draw({0,0});
		font(U"Hello, Siv3D!🐣").draw(s3d::Vec2{30,30});
	});
	/*
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	
	// 大きさ 60 のフォントを用意
	const Font font(60);
	
	// 猫のテクスチャを用意
	const Texture cat(Emoji(U"🐈"));
	
	// 猫の座標
	Vec2 catPos(640, 450);
	
	while (System::Update())
	{
		// テキストを画面の中心に描く
		font(U"Hello, Siv3D!🐣").drawAt(Scene::Center(), Palette::Black);
		
		// 大きさをアニメーションさせて猫を表示する
		cat.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(catPos);
		
		// マウスカーソルに追従する半透明の赤い円を描く
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
		
		// [A] キーが押されたら
		if (KeyA.down())
		{
			// Hello とデバッグ表示する
			Print << U"Hello!";
		}
		
		// ボタンが押されたら
		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			// 猫の座標を画面内のランダムな位置に移動する
			catPos = RandomVec2(Scene::Rect());
		}
	} */
}
