/**********************************************************************************************************
                                天穹飞控 —— 致力于打造中国最好的多旋翼开源飞控
                                Github: github.com/loveuav/BlueSkyFlightControl
                                技术讨论：bbs.loveuav.com/forum-68-1.html
 * @文件     flightStatus.c
 * @说明     飞行状态分类与检测
 * @版本  	 V1.0
 * @作者     BlueSky
 * @网站     bbs.loveuav.com
 * @日期     2018.05 
**********************************************************************************************************/
#include "flightStatus.h"

typedef struct
{
    uint8_t init;           //初始化状态
    uint8_t failsafe;       //失控保护状态
	uint8_t armed;          //电机锁定状态
	uint8_t flight;         //飞行状态
	uint8_t placement;      //放置状态
	uint8_t altControl;     //高度控制状态
	uint8_t posControl;     //位置控制状态
	uint8_t mode;
}FLIGHT_STATUS_t;

FLIGHT_STATUS_t flyStatus;


void SetArmedStatus(uint8_t status)
{
	if(status == DISARMED)	//上锁
	{	
		
	}
	else if(status == ARMED)	//解锁
	{	
		
	}
}

uint8_t GetArmedStatus(void)
{
    return flyStatus.armed;
}

/**********************************************************************************************************
*函 数 名: PlaceStausCheck
*功能说明: 飞行器放置状态检测：静止或运动
*形    参: 角速度
*返 回 值: 无
**********************************************************************************************************/
void PlaceStausCheck(Vector3f_t gyro)
{
    Vector3f_t gyroDiff;
    static Vector3f_t lastGyro;
    static float threshold = 1.0f;
    static uint16_t checkNum = 0;
    static int16_t count = 0;
    
    gyroDiff.x = gyro.x - lastGyro.x;
    gyroDiff.y = gyro.y - lastGyro.y;    
    gyroDiff.z = gyro.z - lastGyro.z;
    lastGyro = gyro;
    
    if(count < 100)
    {
        count++;
        //陀螺仪数值变化大于阈值
        if(abs(gyroDiff.x) > threshold || abs(gyroDiff.y) > threshold || abs(gyroDiff.z) > threshold)
        {
            checkNum++;
        }
    }
    else
    {
        //陀螺仪数据抖动次数大于一定值时认为飞机不处于静止状态
        if(checkNum > 30)
            flyStatus.placement = MOTIONAL;
        else
            flyStatus.placement = STATIC;
        
        checkNum = 0;
        count = 0;
    }  
}

/**********************************************************************************************************
*函 数 名: GetPlaceStatus
*功能说明: 获取飞行器放置状态
*形    参: 无
*返 回 值: 状态
**********************************************************************************************************/
uint8_t GetPlaceStatus(void)
{
    return flyStatus.placement;    
}

/**********************************************************************************************************
*函 数 名: SetAltControlStatus
*功能说明: 设置当前的高度控制状态
*形    参: 状态
*返 回 值: 无
**********************************************************************************************************/
void SetAltControlStatus(uint8_t status)
{
    flyStatus.altControl = status;    
}

/**********************************************************************************************************
*函 数 名: GetAltControlStatus
*功能说明: 设置当前的高度控制状态
*形    参: 状态
*返 回 值: 无
**********************************************************************************************************/
uint8_t GetAltControlStatus(void)
{
    return flyStatus.altControl;    
}

/**********************************************************************************************************
*函 数 名: SetPosControlStatus
*功能说明: 设置当前的位置控制状态
*形    参: 状态
*返 回 值: 无
**********************************************************************************************************/
void SetPosControlStatus(uint8_t status)
{
    flyStatus.posControl = status;    
}

/**********************************************************************************************************
*函 数 名: GetPosControlStatus
*功能说明: 获取当前的位置控制状态
*形    参: 无
*返 回 值: 状态
**********************************************************************************************************/
uint8_t GetPosControlStatus(void)
{
    return flyStatus.posControl;    
}

/**********************************************************************************************************
*函 数 名: SetInitStatus
*功能说明: 设置飞控初始化状态
*形    参: 无
*返 回 值: 状态
**********************************************************************************************************/
void SetInitStatus(uint8_t status)
{
    flyStatus.init = status;    
}

/**********************************************************************************************************
*函 数 名: GetInitStatus
*功能说明: 获取飞控初始化状态
*形    参: 无
*返 回 值: 状态
**********************************************************************************************************/
uint8_t GetInitStatus(void)
{
    return flyStatus.init;    
}


/**********************************************************************************************************
*函 数 名: GetFlightMode
*功能说明: 获取当前的飞行模式
*形    参: 无
*返 回 值: 模式
**********************************************************************************************************/
uint8_t GetFlightMode(void)
{
    return flyStatus.mode;    
}





