// /d/xiangyang/eroad1.c

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "青龙门内街");
	set("long", @LONG
这里是军事重镇襄阳城的东门内，不时地有顶盔贯甲的士兵走来走去。向
东出城可以进入安徽、江苏境内。南边有条小巷，小巷两边种着许多大树。北
面是襄阳武馆。
LONG
	);
	set("outdoors", "襄阳");
	set("xyjob", 1);
	set("exits", ([
		"west" : __DIR__"djie2",
		"east" : __DIR__"qinglongmen",
		"north" : __DIR__"damen",
		"south" : __DIR__"ncx5",
	]));

	set("incity",1);
	setup();
}

//Jeep Title调整设置
/*
void init()
{
	object me = this_player();
	object party = me->query("family/family_name");
	switch (party) {
		case "少林派":
			if (me->query("yjj/powerup"))
			{
				me->set("title",HIR"少林派"NOR"·"HIC"易筋经神功传人"NOR);
			}
			else if (me->query("wxjz/jueji"))
			{
				me->set("title",HIR"少林派"HIW"无相无色禅师"NOR);
			}
			else if (me->query("wxjz/pass") && me->query("wxz/done"))
			{
				me->set("title",HIR"少林派无相劫指传人"NOR);
			}
			else if (me->query("family/generation") == 35)
			{
				me->set("title","少林寺无名老僧座下神僧");
			}
		break;
		case "大轮寺":
			if (me->query("quest/wulun/pass"))
			{
				me->set("title",HIB"大轮寺"HIC"五轮明王"NOR);
			}
			else if (me->query("family/master_name") == "鸠摩智")
			{
				me->set("title","大轮寺掌门座下弟子");
			}
			else if (me->query("family/master_name") == "金轮法王")
			{
				me->set("title","大轮寺金轮法王座下弟子");
			}
			else if (me->query("family/generation") == 13)
			{
				me->set("title","大轮寺第十三代弟子");
			}
		break;
		case "峨嵋派":
			if (me->query("emjy/pass"))
			{
				me->set("title",HIR"峨嵋派"HIG"九阳功传人"NOR);
			}
			else if (me->query("emei/jianjue"))
			{
				me->set("title",HIR"峨嵋派回风剑诀传人"NOR);
			}
			else if (me->query("family/master_name") == "风陵师太")
			{
				me->set("title", "峨嵋派三代长老");
			}
		break;
		case "姑苏慕容":
			if (me->query("shenyuan/powerup"))
			{
				me->set("title", HIY"姑苏慕容"HIW"斗转星移传人"NOR);
			}
			else if (me->query("family/master_name") == "慕容博")
			{
				me->set("title", "姑苏慕容第二代弟子");
			}
		break;
		case "古墓派":
			if (me->query("quest/jiuyingm/pass"))
			{
				me->set("title", HIY"古墓派"HIB"活死人"NOR);
			}
			else if (me->query("family/master_name") == "杨过" || me->query("family/master_name") == "小龙女")
			{
				me->set("title", "古墓派神雕侠侣传人");
			}
		break;
		case "华山派":
			if (me->query("huashan/huashan") == "气宗")
			{
				me->delete("huashan/huashan");
				me->set("quest/huashan", "气宗");
			}
			if (me->query("quest/zixia/pass"))
			{
				me->set("title",HIR"华山派"HIM"紫霞功传人"NOR);
			}
			else if (me->query("quest/huashan") == "气宗")
			{
				me->set("title","华山派气宗亲传弟子");
			}
			else if (me->query("quest/huashan") == "剑宗")
			{
				me->set("title","华山派剑宗亲传弟子");
			}
		break;
		case "昆仑派":
			if (me->query("family/master_name") == "何足道")
			{
				me->set("title","昆仑三圣亲传弟子");
			}
		break;
		case "明教":
			if (me->query("mjqkdny/pass"))
			{
				me->set("title",HIY"明教"GRN"乾坤大挪移传人"NOR);
			}
			else if (me->query("family/master_name") == "张无忌")
			{
				me->set("title", "明教教主亲传弟子");
			}
		break;
		case "全真教":
			if (me->query("quanzhen/force") && me->query("quanzhen/force") == "pass")
			{
				me->set("title",HIR"全真教"CYN"先天功传人"NOR);
			}
			else if (me->query("family/generation") == 3)
			{
				me->set("title", "全真七子亲传弟子");
			}
		break;
		case "日月神教":
			if (me->query("family/generation") == 6)
			{
				me->set("title",HIB"日月神教任我行亲传弟子"NOR);
			}
			else if (me->query("family/generation") == 7)
			{
				if (me->query("family/master_name") == "向问天")
				{
					me->set("title", "日月神教光明左使座下堂主");
				}
				else
				{
					me->set("title", "日月神教光明右使座下堂主");
				}
			}
		break;
		case "神龙教":
			if (me->query("family/master_name") == "洪安通")
			{
				me->set("title","神龙教白龙使");
			}
		break;
		case "桃花岛":
			if (me->query("thdjj/ronghe") && me->query("thdjj/ronghe") == "pass")
			{
				me->set("title",HIG"桃花岛"HIR"东邪传人"NOR);
			}
			else if (me->query("family/master_name") == "黄药师")
			{
				me->set("title", "桃花岛主座前弟子");
			}
		break;
		case "天龙寺":
			if (me->query("yideng/ronghe") && me->query("yideng/ronghe") == "pass")
			{
				me->set("title",HIR"大理国"HIY"一阳指传人"NOR);
			}
			else if (me->query("family/master_name") == "一灯大师")
			{
				me->set("title","大理国南帝传人");
			}
			if (me->query("family/master_name") == "一灯大师")
			{
				me->delete("tls"); 
				me->delete("class");
			}
		break;
		case "铁掌帮":
			if (me->query("tiezhang/pass") && me->query("tz/piao"))
			{
				me->set("title",HIB"铁掌帮"MAG"铁掌水上漂"NOR);
			}
			else if (me->query("family/master_name") == "裘千仞")
			{
				me->set("title", "铁掌帮第十四代帮主门下");
			}
			else if (me->query("family/master_name") == "上官剑南")
			{
				me->set("title", "铁掌帮上官帮主弟子");
			}
		break;
		case "武当派":
			if (me->query("quest/tjq/taiji"))
			{
				me->set("title",HIR"武当派太极拳高手"NOR);
			}
		break;
		case "星宿派":
			if (me->query("quest/hgdf/powerup"))
			{
				me->set("title",HIB"星宿派"RED"化功大法传人"NOR);
			}
			else if (me->query("family/master_name") == "丁春秋")
			{
				me->set("title","星宿老怪座前高徒");
			}
		break;
		case "丐帮":
			if (me->query("xlz/sanzhao") && me->query("xlz/sanzhao") == "pass")
			{
				me->set("title",HIY"丐帮"NOR"·"HIM"萧峰挚友"NOR);
			}
			else if (me->query("slbw/pass"))
			{
				me->set("title",HIY"丐帮"HIG"降龙十八掌传人"NOR);
			}
			else if (me->query("gb/baih7g"))
			{
				me->set("title","丐帮洪七公亲传弟子");
			}
			else if (me->query("gb/bags") == 9)
			{
				me->set("title", "丐帮九袋长老");
			}
		break;
		case "嵩山派":
			if (me->query("family/master_name") == "左冷禅")
			{
				me->set("title","五岳盟主亲传弟子");
			}
		break;
		default:
		break;
	}
	if (me->query("quest/shenzhao/diyun"))
	{
		me->set("title",MAG"神照经"NOR"·"HIG"传人"NOR);
	}
	if (me->query("quest/金蛇剑法/pass"))
	{
		me->set("title",HIY"金蛇郎君"NOR"·"HIG"传人"NOR);
	}
	if (me->query("oyf/hamagong") > 2)
	{
		me->set("title",HIW"白驼山庄"NOR"·"HIG"西毒传人"NOR);
	}
	else if (me->query("oyf/hamagong") == 2)
	{
		me->set("title",HIW"白驼山庄"NOR"·"HIB"蛤蟆功传人"NOR);
	}
	else if (me->query("oyf/hamagong") == 1)
	{
		me->set("title",HIW"白驼山庄"NOR"·"MAG"欧阳锋义子"NOR);
	}

	if (me->query("job_time/神龙岛海战") && (int)me->query("job_time/神龙岛海战") > 0)
	{
		int times = (int)me->query("job_time/神龙岛海战");
		me->delete("job_time/神龙岛海战");
		me->add("job_time/大清国海战", times);
	}
}
*/

/*
void init()
{
	object me= this_player();
	if ( me->query("oldsj")) {
		if ( !me->query("bxsj_bonus/age")) {
			if (me->query("mud_age") > 7840000)
				me->set("mud_age", 7840000);
			me->set("bxsj_bonus/age", 1);
		}
	}
	// 部分 Skill 调整
	if ( me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);
	if ( me->query_skill("bangjue", 1) > 200)
		me->set_skill("bangjue", 200 );
	if ( me->query_skill("checking", 1) > 200)
		me->set_skill("checking", 200 );
	if ( me->query_skill("stealing", 1) > 200)
		me->set_skill("stealing", 200 );
	if ( me->query_skill("checking", 1) > 200)
		me->set_skill("checking", 200 );
	if ( me->query_skill("dagou-zhen", 1) > 200)
		me->set_skill("dagou-zhen", 200 );
	if ( me->query_skill("begging", 1) > 200)
		me->set_skill("begging", 200 );
	if ( me->query_skill("poison", 1) > 200)
		me->set_skill("poison", 200 );
	if ( me->query_skill("buddhism", 1) > 200)
		me->set_skill("buddhism", 200 );
	if ( me->query_skill("taoism", 1) > 200)
		me->set_skill("taoism", 200 );
	if ( me->query_skill("huanxi-chan", 1) > 200)
		me->set_skill("huanxi-chan", 200 );

	if (! me->query("tls")
	 && me->query_skill("liumai-shenjian", 1)){
		me->delete_skill("liumai-shenjian", 1);
		tell_object(me, HIG"天龙寺俗家弟子系统自动去掉六脉神剑。\n"NOR);
	}


	if ( me->query("oldsj") && me->query("bxsj_bonus/no_pk")){
		if ( time() - me->query("bxsj_bonus/no_pk") > 1296000 ){
			me->delete("no_pk");
			me->delete("bxsj_bonus/no_pk");
			tell_object(me,HIG"\n15天时间已到，系统自动帮您解除金盆洗手状态。\n"NOR);

		}
	}

}
*/