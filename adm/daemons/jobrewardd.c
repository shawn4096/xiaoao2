// 统一控制所有任务奖励。by lsxk  2008/1/7
// By Spiderii@ty 加个东东。洗手的JOB奖励比不洗手的降低一些
// By Spiderii@ty 转生玩家pot上限的限制。。刺激玩家转生
// update by lsxk@hsbbs 2008/06/27 添加转生玩家潜能上限限定
// Update by Jpei@feixue 放宽hardquo，修改描述。增加三种vip的识别


/* 参数说明：
    obj:    玩家自身
    job:    任务名称
    shenflag:    正负神标志,正神为1，负神为-1，不奖励神为0.
    potflag:    潜能标志，传递1，潜能超上限给，否则不超上限。
    credit:    通宝标志，0为无通宝奖励，-1为让系统根据经验值奖励计算通宝奖励，其他数值为指定通宝奖励数值.
    hardquo:    难度系数，数值从-10到20，数值越高，说明难度高，所以奖励多。负数的时候，奖励将会小于基础奖励。-10,经验奖励为0，奖励maxexp数量的潜能。
    PVPquo:    是否是玩家VS玩家类型的任务，即互动任务，如是，则请传递该PVP任务奖励加成系数(1-10)，否则为0.
    PVPlvl:    PVP类型任务奖励等级。例如襄阳任务：成功杀了3个对方的人，这个数值就是3。看任务标记。
    maxexp:    最大EXP数值，如果计算出来的EXP奖励大于这个，则取这个值。在计算加成奖励之前有效。为0则不限制。
    giver:    谁给的奖励，方便调用GIFT_D进行随机奖励。
*/

//全局定义基础经验值奖励
#define BASEEXP 50
//全局定义PVP类型任务基础经验奖励.
#define PVPEXP 180

//全局定义限定玩家增长的EXP上限为7500M
#define LIMITEXP 7500000000

//全局定义转生玩家潜能奖励基础上限为50000点
#define LIMITPOT 50000

//定义VIP Player的奖励加成系数，注意计算方式为：exp + exp * VIP奖励加成系数 / 100
#define VIPQUO 1

//定义节日奖励加成参数，注意计算方式为：exp + exp * 节日加成系数 / 10 
#define FESTIVAL 1

//定义试剑山庄进入奖励的最低EXP限制。
#define ENTER_MIN_EXP 2000000

#include <ansi.h>;

int get_reward(object obj, string job, int shenflag, int potflag, int credit, int hardquo, int PVPquo, int PVPlvl, int maxexp, mixed giver)
{
    int exp,vipexp,expquo, pot, shen,exprelife,t;
	int a;
    object ebook;
    string msg;
   


    msg = HIR"恭喜你！你成功的完成了" + HIG + job + HIR + "任务！你被奖励了：\n" + NOR;

//如果不是PVP类型，则基础经验奖励取全局定义，否则取PVP数值。
    if(!PVPquo){

//经验值部分
// 25m前，全部都是正常增长速度
// 25到35之间为50%增速发展
// 35到75之间为20%的增速
// 75m后停止增长
// 若洗手则0.8倍惩罚


if (obj->query("combat_exp")<5000000) exp = BASEEXP;
if (obj->query("combat_exp")>=5000000 && obj->query("combat_exp")<=15000000) exp = BASEEXP;
if (obj->query("combat_exp")>=15000000 && obj->query("combat_exp")<=25000000) exp = BASEEXP;
if (obj->query("combat_exp")>25000000 && obj->query("combat_exp")<=35000000) exp = BASEEXP * 0.5;
if (obj->query("combat_exp")>35000000) exp = BASEEXP * 0.5;
//if (obj->query("combat_exp")>75000000) exp = BASEEXP * 0;
//洗手惩罚20%
//取消洗手惩罚
       //if(obj->query("no_pk")) exp = exp * 0.8;

        if(obj->query("no_pk")) a=30000;
		else a=10000;
        
        //if(hardquo > 20) hardquo = 20;
		if(hardquo < -10) hardquo = -10;
         switch (job)
         {
           case "武当":
		   case "星宿叛徒":
		       exp=exp;
		       break;
		   case "雪山":
			   exp=1.1*exp;
		       break;
		   case "日月复兴":
			   exp=1.2*exp;
		       break;
		   case "天地会":
               exp=1.4*exp;
		       break;
		   default:
			   exp=exp;
		       break;
          }
      
        if(hardquo >= 0)
            exp = exp + exp * hardquo /10 + (random(exp)+1) * hardquo /10;
        else
            exp = exp + exp * hardquo /10 - random( -1 * exp * hardquo /10);

        if(hardquo == -10)
            exp = 0;
        if(hardquo > 20)   
           exp = exp * 1.5; //2.5 改成 1.5
    }
    else{

//经验部分
        exp = PVPEXP;
        if(PVPquo > 10) PVPquo = 10;
        if(PVPquo < 0) PVPquo = 0;
        exp = exp + exp * PVPquo / 10 + random(50);  //计算最基础部分经验，即，不论输赢，参加的人都有。
        exp = exp + (exp - PVPEXP) * PVPquo * PVPlvl;  //计算额外奖励部分，也就是获得PVPlvl越多，奖励越多。
    }


// 节日加成部分。
            exp = exp + exp * FESTIVAL / 10;

//参悟武学的经验获取部分，上限点数20点。
        
        
		
//查看EXP是否超标
        if(maxexp != 0 && exp > maxexp)
            exp = maxexp + random(maxexp/10);

		
//这给与vip奖励	
       vipexp=0;
	   
		if(obj->query("buyvip") )
            vipexp = exp * VIPQUO * 20/ 100;
		else if(obj->query("y-card-vip"))
            vipexp =exp * VIPQUO * 10 / 100;
		else if(obj->query("m-card-vip"))
			//vipexp=0;
            vipexp =exp * VIPQUO * 1 / 100;
			//因为月卡是标配，所以月卡奖励调整
	   exp=exp+vipexp;
	   
//was层数累计 层数翻倍，10层100 20层400点
		exp=exp+PVPlvl*PVPlvl;
		
	if(obj->query("relife/exp_ext")){
           exprelife=exp*(int)obj->query("relife/exp_ext",1) / 20;
        }

// 限定玩家EXP到达上限后，极大程度地降低经验奖励。
        if(obj->query("combat_exp") > LIMITEXP){
            exp =  exp * 5 /100;
            tell_object(obj,"你觉得自己最近心神不宁，对武学的研究已经进入了举步惟艰的程度，似乎就是江湖传说的『"+HIG+"武学障"+NOR+"』。\n");
        }

        msg += HIW + chinese_number(exp) + HIC + "点" + HIM + "经验!\n"NOR;

//潜能部分
        //pot = exp / 3;
		pot=100+random(50);

        if(hardquo == -10)
            pot = maxexp;

        msg += HIW + chinese_number(pot) + HIC + "点" + HIY + "潜能!\n"NOR;



//shen部分
        if(shenflag==1){
            //shen = exp / 2 + random(exp / 6);
			shen = 20 + random(10);
            msg += HIW + chinese_number(shen) + HIC + "点正神！\n"NOR;
        }
        else if(shenflag == -1){
           // shen = - exp / 2 - random(exp / 6);
			shen = - 50 - random(10);
            msg += HIW + chinese_number(-shen) + HIC + "点" + HIR + "负神！\n"NOR;
        }
		else if(shenflag == 2){
           // shen = - exp / 2 - random(exp / 6);
		    if (PVPlvl>11) shen = 2000 + random(1000);
			else shen=50 + random(100);
            msg += HIW + chinese_number(shen) + HIC + "点" + HIR + "正神！\n"NOR;
        }
        else shen = 0;

//通宝部分
/*
        if(credit < 0) credit = random(exp / 100);
		if (credit>1 && !obj->query("no_pk")) credit=1+random(1);//限制通宝数,只有非洗手玩家可以获得		
        if(credit != 0) msg += HIW + chinese_number(credit) + HIC + "个" + HIW + "通宝！\n"NOR;
*/
//特殊部分，双倍经验
		credit=0; //设定所有tb为0
        
		expquo = 0;
        if(obj->query_condition("db_exp")){  // 双倍经验
            expquo = exp;
            msg += HIY + "双倍经验奖励期间，你额外地得到了" + HIW + chinese_number(expquo) + HIC + "点" + HIM + "经验！\n"NOR;
        }

//参悟武学EXP加成的描述
       if(obj->query("relife/exp_ext")) 
        msg += HBYEL + "你静下心来，反复回想刚才的任务过程，不禁豁然开朗。。你额外地得到了" + HIW + chinese_number(exprelife) + HIC + "点" + HIM + "经验！\n\n"NOR;
   
      
	   obj->add("shen",shen);
       obj->add("combat_exp",exp+exprelife+expquo);
       obj->add("potential",pot);

    if(potflag != 1 && obj->query("potential") > obj->query("max_pot") && !obj->query("relife/times"))
       obj->set("potential",obj->query("max_pot"));

    if(obj->query("relife/times") && obj->query("potential") > LIMITPOT * (int)obj->query("relife/times"))
       obj->set("potential",LIMITPOT * (int)obj->query("relife/times"));
      
     //  obj->add("SJ_Credit",credit);
       obj->add("job_time/"+job, 1);
	   //增加当前昨晚的工作内容
	   obj->set("job_name",job);

       tell_object(obj,msg);
	   

//180:     log_file( "jobreward/"+job,sprintf("%s(%s)成功完成第%d次%s任务,获得 EXP:%d, EXPQUO:%d, POT:%d, SHEN:%d, CREDIT:%d"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job,exp,expquo,pot,shen,credit));
    
    //增加ebook的难度，由30000调成60000，防止过快，这也是稀缺资源。
       if( random(a) == 100
        && random(500) < ( obj->query("int") + obj->query("str") + obj->query("dex") + obj->query("con") )
        && obj->query("combat_exp",1) >= ENTER_MIN_EXP && (obj->query("y-card-vip") || obj->query("buyvip") ))
   	{
    
       //tell_object(obj, HIW"你行走江湖，对各地的风土人情偶有所得，不由得有了一丝感悟的见解。你获得了一块"HIY"试剑山庄令牌"HIW"！\n"NOR);	   
	   if (!obj->query("no_pk")&& !random(20))
	   {
		   tell_object(obj, HIY"你快意恩仇，杀气凛然，一看就是杀伐果断之辈，额外获得一些黄金！\n"NOR);
		   new("clone/money/gold")->move(obj);
	   }
       ebook=new("/d/sjsz/obj/sjsz_ling");
       ebook->move(obj);
	   //CHANNEL_D->do_channel(this_object(), "rumor",sprintf("有人看到%s弄到了一枚%s！", obj->name(1), ebook->query("name")));
       log_file("jobreward/ebook",sprintf("%s(%s)成功完成第%d次%s任务时获得一块试剑山庄令牌！\n"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job));
    }

    if(giver)
        GIFT_D->check_count(obj,giver,job,0);
    return 1;
}
