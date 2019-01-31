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
#define BASEEXP 60
//全局定义PVP类型任务基础经验奖励.
#define PVPEXP 180

//全局定义限定玩家增长的EXP上限为75M
#define LIMITEXP 75000000

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
	int exp, expquo, pot, shen,exprelife,t;
	object ebook;
	string msg;

    msg = HIW"恭喜你！你成功的完成了" + job + "任务！你被奖励了：\n" + NOR;

	//如果不是PVP类型，则基础经验奖励取全局定义，否则取PVP数值。
	if(!PVPquo){

		//经验值部分
		//0-5m是1.5倍速增长，
		//5m-15m是1.2倍速；
		//分0-15M开始参悟经验为高速成长期*1.5 
		//15-28M为平均速度*1 (因为有参悟经验了)
		//28-35为低速期*0.8 (爆站啊,郁闷啊)
		//35以后慢慢磨吧(参悟4换派玩)
		//计划重新降低增长速度，太快了不好
		// 28m前，全部都是正常增长速度
		// 28到35之间为80%增速发展
		// 35到75之间为50%的增速
		// 75m后停止增长

		if (obj->query("combat_exp") < 5000000) exp = BASEEXP;
		if (obj->query("combat_exp") >= 5000000 && obj->query("combat_exp") <= 15000000) exp = BASEEXP;
		if (obj->query("combat_exp") >= 15000000 && obj->query("combat_exp") <= 25000000) exp = BASEEXP ;
		if (obj->query("combat_exp") > 25000000 && obj->query("combat_exp") <= 35000000) exp = BASEEXP * 0.7;
		if (obj->query("combat_exp") > 35000000) exp = BASEEXP * 0.5;
		if (obj->query("combat_exp") > 75000000) exp = BASEEXP * 0;

		//洗手惩罚20%
		if(obj->query("no_pk")) exp = exp * 0.8;

		//if(hardquo > 20) hardquo = 20;
		if(hardquo < -10) hardquo = -10;
		switch (job)
		{
			case "武当":
				exp = exp;
				break;
			case "雪山":
				exp = 1.1 * exp;
				break;
			case "天地会":
				exp = 1.4 * exp;
				break;
			default:
				exp = exp;
				break;
		}
      
		if(hardquo >= 0)
			exp = exp + exp * hardquo * 3/20 + random(exp * hardquo /20);
		else
			exp = exp + exp * hardquo * 3/20 - random(-1 * exp * hardquo /20);

		if(hardquo == -10)
			exp = 0;

		if(hardquo > 25)   
			exp = exp * 1.5;
		else if(hardquo > 20)
			exp = exp * 1.2;
	}
	else{
		//经验部分
		exp = PVPEXP;
		if(PVPquo > 10) PVPquo = 10;
		if(PVPquo < 0) PVPquo = 0;
		exp = exp + exp * PVPquo / 10 + random(50);  //计算最基础部分经验，即，不论输赢，参加的人都有。
		exp = exp + (exp - PVPEXP) * PVPquo * PVPlvl;  //计算额外奖励部分，也就是获得PVPlvl越多，奖励越多。
	}

	//查看EXP是否超标
	if(maxexp != 0 && exp > maxexp)
		exp = maxexp + random(maxexp/10);

	//普通月卡VIPplayer加成
	if(obj->query("registered") == 3)
		exp = exp + exp * VIPQUO * 1 / 20;

	//年卡VIPplayer加成,标记为y-card-vip
	if(obj->query("y-card-vip"))
		exp = exp + exp * VIPQUO * 1 / 20;

	//终身vip奖励 标记为buyvip
	if(obj->query("buyvip") )
		exp = exp + exp * VIPQUO * 1/ 10;

	//节日加成部分。
	exp = exp + exp * FESTIVAL / 10;

	//参悟武学的经验获取部分，上限点数20点。
	if(obj->query("relife/exp_ext")){
		exprelife = exp * (int)obj->query("relife/exp_ext",1) / 20;
	}

	//限定玩家EXP到达上限后，极大程度地降低经验奖励。
	if(obj->query("combat_exp") > LIMITEXP){
		exp =  exp * 5 /100;
		tell_object(obj,"你觉得自己最近心神不宁，对武学的研究已经进入了举步惟艰的程度，似乎就是江湖传说的『"+HIG+"武学障"+NOR+"』。\n");
	}

	msg += HIW + chinese_number(exp) + "点经验!\n" + NOR;

	//潜能部分
	//pot = exp / 3;
	pot = exp * 3/20 + random(exp/20);

	if(hardquo == -10)
		pot = maxexp;

	msg += HIW + chinese_number(pot) + "点潜能!\n" + NOR;

	//shen部分
	if(shenflag == 1){
		//shen = exp / 2 + random(exp / 6);
		shen = 10 + random(10);
		msg += HIW + chinese_number(shen) + "点正神！\n" + NOR;
	}
	else if(shenflag == -1){
		// shen = - exp / 2 - random(exp / 6);
		shen = - 10 - random(10);
		msg += HIW + chinese_number(-shen) + "点负神！\n" + NOR;
	}
	else shen = 0;

	//通宝部分
	if(credit < 0) credit = random(exp / 100);
	if(credit > 3) credit = 3;//限制通宝数		
	if(credit != 0) msg += HIW + chinese_number(credit) + "个通宝！\n" + NOR;

	//特殊部分，双倍经验
	expquo = 0;
	if(obj->query_condition("db_exp")){  // 双倍经验
		expquo = exp;
		msg += HIY + "双倍经验奖励期间，你额外地得到了" + chinese_number(expquo) + "点经验！\n" + NOR;
	}

	//参悟武学EXP加成的描述
	if(obj->query("relife/exp_ext")) 
		msg += HBYEL + "你静下心来，反复回想刚才的任务过程，不禁豁然开朗。。你额外地得到了" + chinese_number(exprelife) + "点经验！\n\n" + NOR;

	obj->add("combat_exp",exp + exprelife + expquo);
	obj->add("potential",pot);

	if(potflag != 1 && obj->query("potential") > obj->query("max_pot") && !obj->query("relife/times"))
		obj->set("potential",obj->query("max_pot"));

	if(obj->query("relife/times") && obj->query("potential") > LIMITPOT * (int)obj->query("relife/times"))
		obj->set("potential",LIMITPOT * (int)obj->query("relife/times"));

	obj->add("shen",shen);
	obj->add("SJ_Credit",credit);
	obj->add("job_time/"+job, 1);
	tell_object(obj,msg);

	//log_file( "jobreward/"+job,sprintf("%s(%s)成功完成第%d次%s任务,获得 EXP:%d, EXPQUO:%d, POT:%d, SHEN:%d, 
	//CREDIT:%d"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job,exp,expquo,pot,shen,credit));

	//增加ebook的难度，由30000调成60000，防止过快，这也是稀缺资源。
	if( random(30000) == 100
	&& random(500) < ( obj->query("int") + obj->query("str") + obj->query("dex") + obj->query("con") )
	//&& obj->query("combat_exp",1) >= 150000 && (obj->query("y-card-vip") || obj->query("buyvip")|| obj->query("m-card-vip")))
	&& obj->query("combat_exp",1) >= 150000 && (obj->query("y-card-vip") || obj->query("buyvip") ))
	{
		tell_object(obj, HIW"你行走江湖，快意恩仇，对各地的风土人情偶有所得，不由得有了一丝感悟的见解。你获得了一本"HIY"精英之书"HIW"！\n"NOR);
		ebook = new("/u/jpei/ebook");
		ebook->move(obj);
		log_file("jobreward/ebook",sprintf("%s(%s)成功完成第%d次%s任务时获得一本精英之书！\n"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job));
	}

	if(giver)
		GIFT_D->check_count(obj,giver,job,0);
	return 1;
}
