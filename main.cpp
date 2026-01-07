#include <Novice.h>
#include <Math.h>
#define _USE_MATH_DEFINES
#include <algorithm>
#include <String.h>

const char kWindowTitle[] = "GC1A_11_ヨ_カンリン_タイトル";


struct Vector2
{
	float x;
	float y;
};

struct Vector2I
{
	int x;
	int y;
};
Vector2I mouse;
Vector2I premouse;
Vector2I startpoint = {640,320};

struct Drag
{
	Vector2 position;
	int texture;
	unsigned int color;
};

struct Player
{
	Vector2 position;
	Vector2 velocity;
	float speed;
	float direction;
	int size=10;
	int range;
	int status = 0; // 0:初始狀態 1:發射中 2:已發射
	Drag drag[10];
	int texture;
	unsigned int color;
};
Player interceptor[5];
int interceptorInCharge = 0;
int interceptorTimer = 240;
const int interceptorTime = 240;

struct Target
{
	Vector2 position;
	int size=10;
	int hp=3;
	int texture;
	unsigned int color=BLACK;
};
Target target;

struct Stage
{
	int maxInterceptorCount = 3;
	Vector2 targetPosition[5] ;
};
Stage stage[7];
int currentStage = 0;

int Hit(Player a,Target b)
{
	float dx = a.position.x - b.position.x;
	float dy = a.position.y - b.position.y;
	float distance = sqrtf(dx * dx + dy * dy);
	if (distance < (a.range + b.size))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int chargeRange = 250;
int mouseIspressed = 0;
int shotTrigger = 0;
int gamePhase = 3;
int inPhaseControll = 2;
int IPC3_2Status = 0; //0:瞄準 1:發射 飛行 2:resset to 0 3:着弾

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	interceptor[interceptorInCharge].position.x = (float)startpoint.x;
	interceptor[interceptorInCharge].position.y = (float)startpoint.y;
	interceptor[0].color = GREEN;
	interceptor[1].color = BLUE;
	interceptor[2].color = RED;
	interceptor[3].color = BLACK;
	interceptor[4].color = WHITE;
	stage[0].targetPosition[0] = { 200.0f,200.0f };
	stage[0].targetPosition[1] = { 400.0f,300.0f };
	stage[0].targetPosition[2] = { 600.0f,400.0f };
	target.position = stage[currentStage].targetPosition[0];


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
		premouse = mouse;
		Novice::GetMousePosition(&mouse.x, &mouse.y);

		if(gamePhase == 0) //title
		{
			if(inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1) //tutorial
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2) //stage menu
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3) //game

		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2) //main
			{
				float length = (float)sqrt((mouse.y - startpoint.y) * (mouse.y - startpoint.y) + (mouse.x - startpoint.x) * (mouse.x - startpoint.x));
				interceptor[interceptorInCharge].direction = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
				if (IPC3_2Status == 0) //瞄準
				{
					/*if (Novice::IsPressMouse(0) && length > chargeRange)
					{
						if (mouseIspressed == 1)
						{
							mouseIspressed = 1;
						}
						else if (mouseIspressed == 0)
						{
							mouseIspressed = 2;
						}
					}
					else if (Novice::IsPressMouse(0) && length<= chargeRange)
					{
						mouseIspressed = 0;
					}
					else if (mouseIspressed == 1)
					{
						mouseIspressed = 0;
						if(length > 50)
						{
							IPC3_2Status = 1;
							interceptor[interceptorInCharge].status = 1;
							interceptor[interceptorInCharge].speed = 10;
							interceptor[interceptorInCharge].velocity.x = interceptor[interceptorInCharge].speed * -cosf(interceptor[interceptorInCharge].direction);
							interceptor[interceptorInCharge].velocity.y = interceptor[interceptorInCharge].speed * -sinf(interceptor[interceptorInCharge].direction);
						}
					}
					interceptor[interceptorInCharge].direction = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
					if (mouseIspressed == 0)
					{
						if ( length < chargeRange)
						{

							if (Novice::IsPressMouse(0))
							{
								mouseIspressed = 1;
							}
						
						}
					}*/
					if (length > chargeRange && shotTrigger<2)
					{
						shotTrigger = 0;
					}
					else if (length <= chargeRange && shotTrigger < 2)
					{
						shotTrigger = 1;
					}

					if (shotTrigger == 2&&!Novice::IsPressMouse(0))
					{
						if (length > 50)
						{
							interceptor[interceptorInCharge].status = 1;
							interceptor[interceptorInCharge].speed = 10;
							interceptor[interceptorInCharge].velocity.x = interceptor[interceptorInCharge].speed * -cosf(interceptor[interceptorInCharge].direction);
							interceptor[interceptorInCharge].velocity.y = interceptor[interceptorInCharge].speed * -sinf(interceptor[interceptorInCharge].direction);
							IPC3_2Status = 1;
						}
						shotTrigger = 0;
					}
					
					if (Novice::IsPressMouse(0))
					{
						if (shotTrigger == 1)
						{
							shotTrigger = 2;
						}
					}

					if (Novice::IsPressMouse(1))
					{
						IPC3_2Status = 1;
					}
				}
				else if (IPC3_2Status == 1) //發射 飛行
				{
					for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
					{
						interceptor[i].position.x += interceptor[i].velocity.x;
						interceptor[i].position.y += interceptor[i].velocity.y;
						interceptor[i].range = interceptor[i].size + (interceptorTime - interceptorTimer)/6 ;
						//目標命中判定
						
						if (Hit(interceptor[i],target))
						{
							IPC3_2Status = 3;
						}
					}
					interceptorTimer -= 1;
					
					if (interceptorTimer <= 0)
					{
						IPC3_2Status = 2;
						if (interceptorInCharge + 1 < stage[0].maxInterceptorCount)
						{
							interceptorInCharge += 1;
						}
					}
				}
				else if (IPC3_2Status == 2) //命中 時限後  Reset to 0
				{
					interceptor[interceptorInCharge].position.x = (float)startpoint.x;
					interceptor[interceptorInCharge].position.y = (float)startpoint.y;
					for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
					{
						if (interceptor[i].status == 1)
						{
							interceptor[i].position.x = (float)startpoint.x;
							interceptor[i].position.y = (float)startpoint.y;
							interceptor[i].range = interceptor[i].size;
						}
					}
					target.hp = stage[currentStage].maxInterceptorCount;
					target.position.x = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].x;
					target.position.y = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].y;
					interceptorTimer = interceptorTime;
					interceptor[interceptorInCharge].range = interceptor[interceptorInCharge].size;
					IPC3_2Status = 0;
				}
				else if (IPC3_2Status == 3)
				{
					target.hp -= 1;
					target.position.x = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount- target.hp].x;
					target.position.y = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].y;
					IPC3_2Status = 1;
				}

				for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
				{
					if (interceptor[i].position.x < 0 )
					{
						interceptor[i].position.x = 1280;
					}
					if ( interceptor[i].position.x > 1280)
					{
						interceptor[i].position.x = 0;
					}
					if (interceptor[i].position.y < 0 )
					{
						interceptor[i].position.y =720;
					}
					if (interceptor[i].position.y > 720)
					{
						interceptor[i].position.y = 0;
					}
				}
				Novice::ScreenPrintf(0, 20, "theta:%f length:%f", interceptor[interceptorInCharge].direction, length);
			}
			else if (inPhaseControll == 3) //sub
			{
			}
			else if (inPhaseControll == 4)
			{
			}
			else if (inPhaseControll == 5)
			{
			}

			if(keys[DIK_1]&& !preKeys[DIK_1])
			{
				interceptorInCharge = 0;
				IPC3_2Status = 2;
			}
			if (keys[DIK_2] && !preKeys[DIK_2])
			{
				interceptorInCharge = 1;
				IPC3_2Status = 2;
			}
			if (keys[DIK_3] && !preKeys[DIK_3])
			{
				interceptorInCharge = 2;
				IPC3_2Status = 2;
			}

		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (gamePhase == 0)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2)
		{
			
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
				{
					Novice::DrawEllipse((int)interceptor[i].position.x, (int)interceptor[i].position.y, interceptor[i].size, interceptor[i].size, 0.0f, interceptor[i].color, kFillModeSolid);
					Novice::DrawEllipse((int)interceptor[i].position.x, (int)interceptor[i].position.y, interceptor[i].range, interceptor[i].range, 0.0f, interceptor[i].color- 120-(interceptorTime - interceptorTimer)/2, kFillModeSolid);
				}
				Novice::DrawEllipse((int)target.position.x, (int)target.position.y, target.size, target.size, 0.0f, target.color, kFillModeSolid);

				float theta = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
				/*float length = (float)sqrt((mouse.y - startpoint.y) * (mouse.y - startpoint.y) + (mouse.x - startpoint.x) * (mouse.x - startpoint.x));
				if (length > 200)
				{
					length = 200;
				}*/
				float length = 200;
				Novice::ScreenPrintf(0, 0, "mouseX:%d mouseY:%d", mouse.x, mouse.y);
				
				Novice::ScreenPrintf(0, 40, "mouseIspressed:%d IPC3_2Status:%d", mouseIspressed, IPC3_2Status);
				Novice::ScreenPrintf(0, 60, "interceptorInCharge:%d X:%f Y:%f", interceptorInCharge, interceptor[interceptorInCharge].position.x, interceptor[interceptorInCharge].position.y);
				if (IPC3_2Status == 0)
				{
					if (shotTrigger == 2)
					{
						Novice::DrawLine(startpoint.x, startpoint.y, startpoint.x - (int)(length * cosf(theta)), startpoint.y - (int)(length * sinf(theta)), 0xFFFFFFFF);
					}
					Novice::DrawEllipse(startpoint.x, startpoint.y, chargeRange, chargeRange, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
				}
				else if (IPC3_2Status == 1)
				{
					
				}
				else if (IPC3_2Status == 2)
				{
				}
				else if (IPC3_2Status == 3)
				{
				}
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
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
