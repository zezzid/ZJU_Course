//变量初始化，避免误操作
$DC = false;    //车辆控制命令无效
$AC = false;    //舵机控制命令无效
$OutMod = 0;    //不改变下次工作模式
simMode = 0;
//showMsg("演示模式="+(-difference(31,0)));

//内置全局变量安排 ---
//		31		演示步骤变量
//		30		串口数据上次序号记忆
//		29		初始化步骤
//内置模式安排 ---
//		99		初始化模式
//		1		语音交互模式
//		2~98	演示功能模式，即最多可以设置96个功能展示

if($g_activeTimes==0){ //第一次运行
	setValueBase(29,0);				//初始化步骤设置为0
	setValueBase(30,getConfig(25));	//设置串口数据序号初值记录
	$OutMod = 98;
	vrConfig("{r0}");//发送配置命令使得小车退出内置流程
	showMsg("请等候7秒钟");
	setTimeBase(0);
}
else{
	switch($Mod){
		case 98:if( elapsed(0)>7000 )	$OutMod = 99;//等待退出内置流程的语音播报完成
				else showWaitProgress(elapsed(0)/100,70);
				break;
		case 99:Init();//初始化语音模块
			break;
		case 1:	VoiceControl();	//用语音控制演示步骤
			break;
		default:DemoShow();		//执行演示
			break;
	}
}

function GetSerialData()
{
	var sDataIndex = getConfig(25);		//获取当前串口数据序号，即系统已收到的串口数据数。
	var sData = -1;						//无数据时返回-1
	if(-difference(30,0)!=sDataIndex){	//通过判断25号配置数据是否变化来判断串口数据是否有更新
		sData = getConfig(26);
		setValueBase(30,sDataIndex);	//更新当前串口数据序号至内置变量#30
	}
	return sData;
}

function VoiceControl()
{
	//获取串口输入，执行响应
	var sData = GetSerialData();
	//识别成功时，串口返回值为指定返回值（若未指定则返回序号）和128相或的结果
	switch(sData){	
		case 128:	//动一动
			setValueBase(31,1);	//演示步骤--基本动作
			$OutMod = 2;		//演示从Mode 2开始
			break;
		case 129:	//摇摇头
			setValueBase(31,2);//演示步骤--云台动作1
			$OutMod = 2;		//演示从Mode 2开始
			break;
		case 130:	//点点头
			setValueBase(31,3);//演示步骤--云台动作2
			$OutMod = 2;		//演示从Mode 2开始
			break;
		case 131:	//握个爪
			setValueBase(31,4);//演示步骤--机械臂动作1
			$OutMod = 2;		//演示从Mode 2开始
			break;
		case 132:	//抓个球
			setValueBase(31,5);//演示步骤--机械臂动作2
			$OutMod = 2;		//演示从Mode 2开始
			break;
		default:
			break;
	}
}

function DemoShow()
{
	switch(-difference(31,0)){//演示步骤
	case 1://演示小车基本运动
		BaseMotion();
		break;		
	case 2://演示云台运动1
		ShakeHead();
		break;
	case 3://演示云台运动2
		NodHead();
		break;
	case 4://机械臂动作1
		GraspClaw();
		break;
	case 5://机械臂动作2
		CatchBall();
		break;
	case 6:
		showMsg("补充演示步骤3");
		setValueBase(31,0);//演示步骤变量复位
		setTimeBase(0);
		$OutMod = 1;	//返回语音层面
		break;
	//...
	}
}

function BaseMotion()
{
	switch($Mod){
		case 0: break;
		case 1:	break;
		case 2:	
			if( elapsed(0)>1000 && getConfig(24)==2){//上次语音播报完成
				$DC = true;$Dir = 0;//小车前进
				setTimeBase(0);//记下当前时刻
				ttsSpeak("前进");
				$OutMod = 3;
			}
			break;
		case 3:	
			//注意这里如果没有elapsed的判断，可能会导致前面的“前进”还没开始说就执行到这里，
			//从而条件满足直接开始说“后退”，吃掉“前进”，加上一定的延时条件可以防止这一情况。
			if( elapsed(0)>1000 && getConfig(24)==2 ){
				$DC = true;$Dir = 1;//小车后退
				setTimeBase(0);//记下当前时刻
				ttsSpeak("后退");
				$OutMod = 4;
			}
			break;
		case 4:	
			if( elapsed(0)>1000 && getConfig(24)==2 ){
				$DC = true;$Dir = 4;//小车停止
				setTimeBase(0);//记下当前时刻
				ttsSpeak("停止");
				$OutMod = 5;
			}
			break;
		case 5:
			if( elapsed(0)>1000 && getConfig(24)==2){//上次语音播报完成
				$DC = true;$Dir = 2;//小车左转
				setTimeBase(0);//记下当前时刻
				ttsSpeak("左转");
				$OutMod = 6;
			}
			break;
		case 6:
			if( elapsed(0)>1000 && getConfig(24)==2){//上次语音播报完成
				$DC = true;$Dir = 3;//小车右转
				setTimeBase(0);//记下当前时刻
				ttsSpeak("右转");
				$OutMod = 7;
			}
			break;
		case 7:
			if( elapsed(0)>1000 && getConfig(24)==2 ){
				$DC = true;$Dir = 4;//小车停止
				setTimeBase(0);//记下当前时刻
				ttsSpeak("停止");
				$OutMod = 8;
			}
			break;
		//...
		default:
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("完成");
				setValueBase(31,0);//演示步骤变量复位
				setTimeBase(0);
				$OutMod = 1;	//返回语音层面
			}
			break;
	}
}

function ShakeHead()
{
	switch($Mod){
		case 0: break;
		case 1:	break;
		case 2:	
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("摇头开始");
				$OutMod = 3;
			}
			break;
		case 3:	//开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=7;$Ang=0;	//水平舵机转到底
				setTimeBase(0);			//记下当前时刻
				$OutMod = 4;
				ttsSpeak("左");
			}
			break;
		case 4:	//左转头
			if( elapsed(0)<=1800 ){//1800毫秒转头180度
				$AC=true;$ID=7;$Ang=elapsed(0)/10;	//水平舵机按时转动
			}
			else{
				$OutMod = 5;
			}
			break;
		case 5:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=7;$Ang=180;//水平舵机转到底
				setTimeBase(0);			//记下当前时刻
				$OutMod = 6;
				ttsSpeak("右");
			}
			break;
		case 6: //右转头
			if( elapsed(0)<=1800 ){//1800毫秒转头180度
				$AC=true;$ID=7;$Ang=180 - elapsed(0)/10;	//水平舵机按时转动
			}
			else{
				$OutMod = 7;
			}
			break;
		case 7:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=7;$Ang=90;//水平舵机恢复朝前
				//setTimeBase(0);			
				$OutMod = 8;
				ttsSpeak("恢复");
			}
			break;
		
		//...
		default:
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("完成");
				setValueBase(31,0);//演示步骤变量复位
				setTimeBase(0);
				$OutMod = 1;	//返回语音层面
			}
			break;
	}
}

function NodHead()
{
	switch($Mod){
		case 0: break;
		case 1:	break;
		case 2:	
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("点头开始");
				$OutMod = 3;
			}
			break;
		case 3:	//开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=8;$Ang=0;	//垂直舵机转到底
				setTimeBase(0);			//记下当前时刻
				$OutMod = 4;
				ttsSpeak("上");
			}
			break;
		case 4:	//向上抬头
			if( elapsed(0)<=900 ){//900毫秒转头180度
				$AC=true;$ID=8;$Ang=elapsed(0)/10;	//垂直舵机按时转动
			}
			else{
				$OutMod = 5;
			}
			break;
		case 5:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=8;$Ang=90;//垂直舵机转到底
				setTimeBase(0);			//记下当前时刻
				$OutMod = 6;
				ttsSpeak("下");
			}
			break;
		case 6: //向下点头
			if( elapsed(0)<=900 ){//900毫秒转头180度
				$AC=true;$ID=8;$Ang=90-elapsed(0)/10;	//垂直舵机按时转动
			}
			else{
				$OutMod = 7;
			}
			break;
		case 7:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=8;$Ang=0;//垂直舵机恢复朝前
				//setTimeBase(0);			
				$OutMod = 8;
				ttsSpeak("恢复");
			}
			break;
		//...
		default:
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("完成");
				setValueBase(31,0);//演示步骤变量复位
				setTimeBase(0);
				$OutMod = 1;	//返回语音层面
			}
			break;
	}
}

function GraspClaw()
{
	switch($Mod){
		case 0: break;
		case 1:	break;
		case 2:	
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("握个爪开始");
				$OutMod = 3;
			}
			break;
		case 3:	//开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=4;$Ang=160;	//4号舵机控制机械爪握住
				setTimeBase(0);			//记下当前时刻
				$OutMod = 4;
				ttsSpeak("张开");
			}
			break;
		case 4:	//张开
			if( elapsed(0)<=800 ){//800毫秒转动160度
				$AC=true;$ID=4;$Ang=160 - elapsed(0)/5;	//4号舵机按时转动，使机械爪张开
			}
			else{
				$OutMod = 5;
			}
			break;
		case 5:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=4;$Ang=0;//4号舵机控制机械爪张开
				setTimeBase(0);			//记下当前时刻
				$OutMod = 6;
				ttsSpeak("握住");
			}
			break;
		case 6: //握住
			if( elapsed(0)<=800 ){//800毫秒转头160度
				$AC=true;$ID=4;$Ang=elapsed(0)/5;	//4号舵机按时转动，使机械爪握住
			}
			else{
				$OutMod = 7;
			}
			break;
		
		//...
		default:
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("完成");
				setValueBase(31,0);//演示步骤变量复位
				setTimeBase(0);
				$OutMod = 1;	//返回语音层面
			}
			break;
	}
}

function CatchBall()
{
	switch($Mod){
		case 0: break;
		case 1:	break;
		case 2:	
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("抓个球开始");
				//$AC=true;$ID=2;$Ang=100;//控制2号舵机维持固定角度
				//$AC=true;$ID=3;$Ang=90;//控制3号舵机维持固定角度
				$OutMod = 3;
			}
			break;
		case 3:	//开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=1;$Ang=150;	//控制1号舵机往下碰到球
				setTimeBase(0);			//记下当前时刻
				$OutMod = 4;
				ttsSpeak("往下");
			}
			break;
		case 4:	//机械臂往下
			if( elapsed(0)<=300 ){//300毫秒转头60度
				$AC=true;$ID=1;$Ang=150 - elapsed(0)/5;	//1号舵机按时转动
			}
			else{
				$OutMod = 5;
			}
			break;
		case 5:	//再次开始
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=4;$Ang=0;//4号舵机控制机械爪张开
				setTimeBase(0);			//记下当前时刻
				$OutMod = 6;
				ttsSpeak("抓球");
			}
			break;
		case 6: //抓球
			if( elapsed(0)<=1600 ){//800毫秒转头160度
				$AC=true;$ID=4;$Ang=elapsed(0)/10;	//4号舵机按时转动
			}
			else{
				$OutMod = 7;
			}
			break;
		case 7:
			if(getConfig(24)==2){		//上次语音播报完成
				$AC=true;$ID=1;$Ang=90;	//1号舵机处于靠近地面的状态
				setTimeBase(0);			//记下当前时刻
				$OutMod = 8;
				ttsSpeak("举起");
			}
			break;
		case 8:	//举起小球
			if( elapsed(0)<=300 ){//300毫秒转头60度
				$AC=true;$ID=1;$Ang=90 + elapsed(0)/5;	//1号舵机按时转动
			}
			else{
				$OutMod = 9;
			}
			break;
		//...
		default:
			if(getConfig(24)==2){//上次语音播报完成
				ttsSpeak("完成");
				setValueBase(31,0);//演示步骤变量复位
				setTimeBase(0);
				$OutMod = 1;	//返回语音层面
			}
			break;
	}
}

function VR_Wait_Cfg(sCfg,next)
{
	var sData = GetSerialData();
	if( elapsed(0)>1000 || sData==198 || sData==136 ){//超时了或串口数据符合要求进入
		if( sCfg!="" )
			vrConfig(sCfg);
		setValueBase(29,next);
		setTimeBase(0);//设置计时起点
		return !(sData==198 || sData==136);//超时返回true
	}
	return false;
}

function Init(){
	//语音配置代码
	switch(-difference(29,0)){
		case 0:	vrConfig("{c0}");
				setValueBase(29,1);
				setTimeBase(0);//设置计时起点
				break;
		case 1:	if( VR_Wait_Cfg("",2) ) setValueBase(29,100);//c0超时
				break;
		case 2:	if( simMode )
					VR_Wait_Cfg("{a0基本动作|x000}",3);//动一动
				else
					VR_Wait_Cfg("{a0ji ben dong zuo|x000}",3);//动一动					
				break;
		case 3:	if( simMode )
					VR_Wait_Cfg("{a0摇头晃脑|x001}",4);//摇摇头
				else
					VR_Wait_Cfg("{a0yao tou huang nao|x001}",4);//摇摇头

				break;
		case 4:	if( simMode )
					VR_Wait_Cfg("{a0点头示意|x002}",5);//点点头
				else
					VR_Wait_Cfg("{a0dian tou shi yi|x002}",5);//点点头
				break;
		case 5:	if( simMode )
					VR_Wait_Cfg("{a0友好握爪|x003}",6);//握个爪
				else
					VR_Wait_Cfg("{a0you hao wo zhua|x003}",6);//握个爪
				break;
		case 6:	if( simMode )
					VR_Wait_Cfg("{a0抓个小球|x004}",7);//抓个球
				else
					VR_Wait_Cfg("{a0zhua ge xiao qiu|x004}",7);//抓个球
				break;
		case 7: if( simMode )
					VR_Wait_Cfg("{CF}",8);//更新配置
				else
					VR_Wait_Cfg("",8);//无意义操作，纯为了等待前面操作完成。
				break;
		//...
		default:if( elapsed(0)>2000 ){
					if( -difference(29,0)!=100 )	ttsSpeak("语音模块准备完成");
					else 							ttsSpeak("语音模块准备失败");
					setValueBase(29,0);//恢复29号变量为0
					setValueBase(31,0);//设置演示步骤变量初值
					$OutMod = 1;//进入语音层
				}
				break;
	}
}
