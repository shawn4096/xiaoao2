#include <ansi.h>
#include <database.h>

#define REJOIN_CMD      "/cmds/std/rejoin.c"
#define GIFT_CMD        "/cmds/common/gift"
//#define LD		"/adm/daemons/lotteryd"

int new_gift = 0;

void create()
{
	seteuid(getuid());
	GIFT_CMD->create();
}

int have_new_gift()
{
	if ( new_gift ) return new_gift = 0;
	return new_gift = 1;
}

int query_new_gift() { return new_gift; }

void check_user_weapon(object me);

void get_cloth(object user)
{
	object cloth;
	int i,vip;
	string fam = user->query("family/family_name");
	string title1,title2;
	
		
	i = user->query("family/generation");

	switch(fam) {
		case "少林派":
			if (i <= 35) cloth = new("/d/shaolin/obj/du-cloth");
			if (i == 36) cloth = new("/d/shaolin/obj/xuan-cloth");
			if (i == 37) cloth = new("/d/shaolin/obj/cheng-cloth");
			if (i == 38) cloth = new("/d/shaolin/obj/hui-cloth");
			if (i == 39) cloth = new("/d/shaolin/obj/dao-cloth");
			if (i == 40) cloth = new("/d/shaolin/obj/qing-cloth");
			if (i >= 41) cloth = new("/d/shaolin/obj/cloth");
			if (i < 41 && userp(user))
				switch (user->query("name")[0..1]) {
					case "净":
					case "明":
					case "空":
					case "虚":
						user->set("class", "huanxi");
				}
			break;
		case "明教":
			if (i <= 35) {
				if(user->query("family/master_name") == "张无忌")
					cloth = new("/d/mingjiao/obj/white-cloth");
				else cloth = new("/d/mingjiao/obj/yel-cloth");
			}
			if (i == 36) cloth = new("/d/mingjiao/obj/red-cloth");
			if (i >= 37) cloth = new("/d/mingjiao/obj/green-cloth");
			break;
		case "昆仑派":
		        if (i <= 3 ) cloth = new("/d/kunlun/obj/pao1");
		        if (i == 4 ) cloth = new("/d/kunlun/obj/pao2");
		        if (i == 5 ) cloth = new("/d/kunlun/obj/pao3");
		        if (i == 6 ) cloth = new("/d/kunlun/obj/pao4");
                        break;
		case "峨嵋派":
			if (user->query("class") == "bonze")
				cloth = new("/d/emei/obj/cloth");
			else    cloth = new("/d/emei/obj/cloth2");
			break;
		case "天龙寺":
			if (user->query("tls")) {
				if (i <= 13) cloth = new("/d/tls/obj/jiasha");
				if (i == 14) cloth = new("/d/tls/obj/jiasha1");
				if (i >= 15) cloth = new("/d/tls/obj/jiasha2");
			}
			else {
				if (i <= 14) cloth = new("/d/dali/obj/guanfu1");
				if (i >= 15) cloth = new("/d/dali/obj/guanfu2");
			}
			break;
		case "姑苏慕容":
			if(user->query("gender") == "女性")
			{
				if (i == 2) cloth = new("/d/mr/obj/cloth6");
				if (i == 3) cloth = new("/d/mr/obj/cloth5");
				if (i == 4) cloth = new("/d/mr/obj/cloth4");
			}
			else
			{
				if (i == 2) cloth = new("/d/mr/obj/cloth3");
				if (i == 3) cloth = new("/d/mr/obj/cloth2");
				if (i == 4) cloth = new("/d/mr/obj/cloth1");
			}
			break;
		case "武当派":
			if (i <= 2) cloth = new("/d/wudang/obj/whiterobe");
			if (i >= 3)
				if(user->query("gender") != "女性") cloth = new("/d/wudang/obj/greyrobe");
				else cloth = new("/d/wudang/obj/greenrobe");
			break;
		case "大轮寺":
			if (i <= 11) cloth = new("/d/xueshan/npc/obj/longxiang-jiasha");
			if (i == 12) cloth = new("/d/xueshan/npc/obj/changsheng-jiasha");
			if (i == 13) cloth = new("/d/xueshan/npc/obj/gongde-jiasha");
			if (i >= 14) cloth = new("/d/xueshan/npc/obj/qinxiu-jiasha");
			break;
		case "血刀门":			
			          cloth = new("/d/xuedao/obj/xuepao");
			break;
		case "古墓派":
			if (user->query("gender") =="女性")
				cloth = new("/d/gumu/obj/qun1");
			else
				cloth = new("/d/gumu/obj/pao1");
			break;
		case "嵩山派":
			if(user->query("gender") == "女性"){
				cloth = new(ARMOR_D("cloth"));
				cloth->set("name", HIM "粉红套衫" NOR);
			}
			else cloth = new(ARMOR_D("changpao1"));
			break;
		default:
			cloth = new(ARMOR_D("cloth"));
			if (fam == "星宿派")
				cloth->set("name", YEL "黄葛布衫" NOR);
			if (fam == "华山派")
				cloth->set("name", BLU "劲装" NOR);
			if (fam == "丐帮")
				cloth->set("name", YEL "百衲结衣" NOR);
			if (fam == "桃花岛")
				cloth->set("name", MAG "紫长衫" NOR);
			if (fam == "铁掌帮")
				cloth->set("name", "短打装" );
			if (fam == "神龙教")
				cloth->set("name", "打鱼装" );
			if (fam == "全真教")
				cloth->set("name", HIB"蓝色道袍"NOR );
			if (fam == "灵鹫宫")
				cloth->set("name", HIW"白色霓裳"NOR );
			if (fam == "逍遥派")
				cloth->set("name", HIC"青色鹤氅"NOR );
			if (fam == "日月神教")
				cloth->set("name", HIC"黑袍"NOR );
			if (fam == "白驼山庄")
				cloth->set("name", HIC"白袍"NOR );
			if (!fam && user->query("class") == "bonze")
				cloth->set("name", "僧衣");
	}

	if (cloth) {
		cloth->move(user);
		cloth->wear();
	}

	switch(fam)
	{
		case "姑苏慕容":
			if(user->query("gender") == "女性") cloth = new("/d/mr/obj/xiuhuaxie");
			else cloth = new("/d/mr/obj/guanxue");
			break;
		case "古墓派":
			cloth = new("/d/gumu/obj/buxue1");
			break;
		case "丐帮":
			cloth = new("clone/armor/caoxie");
			break;
		case "全真教":
			cloth = new("clone/armor/shoes");
			cloth->set("name","道履");
			break;
	  case "逍遥派":
			cloth = new("clone/armor/shoes");
			cloth->set("name","玄武靴");
			break;
		case "灵鹫宫":
			cloth = new("clone/armor/shoes");
			cloth->set("name",HIR"绣花小鞋"NOR);
			break;
		default:
			cloth = new("/clone/armor/shoes");
			if (user->query("class") == "bonze") cloth->set("name", "僧鞋");
	}

	if(cloth){
		cloth->move(user);
		cloth->wear();
	}

	if ( fam == "丐帮") {
		i = user->query("gb/bags");
		switch (i) {
			case 0: cloth=new("kungfu/class/gaibang/obj/gb_budai"); break;
			case 1: cloth=new("kungfu/class/gaibang/obj/gb_budai1"); break;
			case 2: cloth=new("kungfu/class/gaibang/obj/gb_budai2"); break;
			case 3: cloth=new("kungfu/class/gaibang/obj/gb_budai3"); break;
			case 4: cloth=new("kungfu/class/gaibang/obj/gb_budai4"); break;
			case 5: cloth=new("kungfu/class/gaibang/obj/gb_budai5"); break;
			case 6: cloth=new("kungfu/class/gaibang/obj/gb_budai6"); break;
			case 7: cloth=new("kungfu/class/gaibang/obj/gb_budai7"); break;
			case 8: cloth=new("kungfu/class/gaibang/obj/gb_budai8"); break;
			case 9: cloth=new("kungfu/class/gaibang/obj/gb_budai9"); break;
			case 10: cloth=new("kungfu/class/gaibang/obj/gb_budai10"); break;
			default : cloth=new("kungfu/class/gaibang/obj/gb_budai"); break;
		}
		if(cloth){
			cloth->move(user);
			cloth->wear();
		}
	}

	// 帮派令牌
	// if (!present("lingpai", user) && user->query("g_name")) new("/data/group/obj/ling")->move(user);

	
       // 结婚信物
	if (user->query("gender") == "女性") {
		if (!present("yu pei", user) && user->query("marry")) new("/clone/misc/marry-token")->move(user);
	} else
		if (!present("xiang nang", user) && user->query("marry")) new("/clone/misc/marry-token")->move(user);

	// class 纠正
	if (user->query("gender") == "无性")
		user->set("class", "eunuch");
	// 性别纠正
	switch (user->query("class")) {
		case "eunach":
			user->set("class", "eunuch");
		case "eunuch":
			user->set("gender", "无性");
		case "emsujia":
			user->delete("class");
		case "bonze":
//                case "huanxi":
		case "lama":
		case "taoist":
			user->delete("marry");
	}
		
	// 生日纠正
	   if (user->query("birthday") + user->query("mud_age") > time())
		user->set("birthday", time() - user->query("mud_age"));
	
	//并站生日纠正 	
			
	//存款纠正
	if(user->query("balance") > F_BANKER->query_balance_limit(user) )
	{
                tell_object(user, HIY "书剑京城总行通知您：因为您的存款数量过多，已经将超额部分按照100黄金:1通宝进行转换，请不要担心。\n" NOR);
		log_file("balance",sprintf("%-19s本来有 %10d 存款，现减为：%10d。\n",user->name(1)+"("+user->query("id")+")", user->query("balance"), F_BANKER->query_balance_limit(user)), user);		
user->add("SJ_Credit", (user->query("balance") - F_BANKER->query_balance_limit(user) )/1000000);
                user->set("balance",F_BANKER->query_balance_limit(user) );
	}

	WORKER_D->check_user_object(user);
	GROUP_D->check_user_group(user);
	//LD->check_user_game(user);
	if (user->query("registered") == 3 && !user->query("vip/rules")){
		tell_object(user, HIY "欢迎您注册成为书剑贵宾玩家，系统已经自动清除了你的桃花源违规记录和离婚记录。\n" NOR);
		user->delete("rules");
		user->delete("divorce");
		user->set("vip/rules",1);
	}
	
	if (new_gift && wizardp(user))
		GIFT_CMD->launching(user);
	
	
	//某些Perform Exert 自动恢复 在这里	
	if(user->query("dali/jujing") && !user->query_temp("dali/jujing") )
	{
		//Jujing /kungfu/skill/qiantian-yiyang/jujing.c
		tell_object(user, HIY"\n时间一长，你感觉支持不住，精神开始分散了。\n" NOR);
		i = user->query("dali/jujing");
				
		user->add("max_jing",i);
		user->add("eff_jing",i);
		if( user->query("jing") > user->query("eff_jing") )
			user->set("jing",user->query("eff_jing"));
		
		if( user->query("eff_qi") > user->query("max_qi") )
			user->set("eff_qi",user->query("max_qi"));
		if( user->query("qi") > user->query("eff_qi") )
			user->set("qi",user->query("eff_qi"));
		
		user->delete_temp("dali/jujing");
		user->delete("dali/jujing");
		user->delete_temp("dali/jujing1");
	}
}

int get_object(object ob, object me)
{
	if( ob->is_character()
	|| ob->query("book")
	|| ob->query("imbued")
	|| ob->query("old_ob") == me ) return 0;
	return ob->query("unique");
}

void check_inventory(object me)
{
	int i , tick_count;
	string desc;
	object *inv;
	object gold;

	if (!objectp(me) || !interactive(me) || !living(me) || (wizardp(me) && !(int)me->query("env/test")) || me->is_fighting()) return;

	if (!new_gift
	|| !userp(me)
	|| me->query("registered") < 2
	|| me->is_ghost()
	|| me->query("mud_age") < 7200
	) ;
	else GIFT_CMD->launching(me);

	if (desc = strip(me->query("long"))) {
		if (strsrch(desc, "\n") > 80) {
			me->delete("long");
			tell_object(me, "你的描述太长了，请重新 describe\n");
		} else if (strsrch(desc, "杀死你") > 5) {
			me->delete("long");
			tell_object(me, "你的描述容易让人误会，请重新 describe\n");
		} else if (desc[<1] != '\n')
			me->set("long", desc+"\n");
	}

	
	//vip 洗手
	if(me->query("registered")==2 && me->query("no_pk"))
	{
		me->set("no_pk_vip",me->query("no_pk"));
		me->set("no_pk_PKS",me->query("PKS"));
		me->delete("no_pk");
		tell_object(me,YEL"您已经不是贵宾用户了，系统取消了您的金盆洗手；请及时激活您的贵宾恢复洗手状态。\n"NOR);
		tell_object(me,HIR"提醒：如果您在这段等待续费的非洗手状态下杀害了其他玩家，那么系统会认为你重出江湖，而且按照程序进行处罚。\n"NOR);
	}
		
	if(me->query("registered")==3 && me->query("no_pk_vip"))
	{
		if(me->query("PKS") <= me->query("no_pk_PKS"))
		{
			me->set("no_pk",me->query("no_pk_vip"));
			me->delete("no_pk_vip");
			me->delete("no_pk_PKS");
			tell_object(me,YEL"您的洗手状态已经恢复。\n"NOR);
		}
		else
		{
			me->set("no_pk",1);
			me->set("prepare_rejoin",1);
			tell_object(me,YEL"您在等待续费的非洗手期间杀害了其他玩家，所以你要重出江湖！\n"NOR);
			REJOIN_CMD->main(me);
			me->delete("no_pk_vip");
			me->delete("no_pk_PKS");			
		}
	}
	//End
	if( me->query("registered")==2 && me->query("online_total") > 180000 ) me->set("online_total",172800);
				
	tick_count++;
	if( tick_count>45 ) {
		switch (me->query_user_type()) {
			case "worker":
				if (i = me->query("no_pk")) {
					me->delete("no_pk");
					me->set("no_pk_disable", i);
					tell_object(me, "你已经不是武士了，洗手标志被自动关闭，在你恢复武士身份后，洗手标志也将自动恢复。\n");
				}
				break;
			default:
				if (i = me->query("no_pk_disable")) {
					me->delete("no_pk_disable");
					me->set("no_pk", i);
					tell_object(me, "你已经恢复武士身份，洗手标志自动恢复。\n");
				}
		}
		tick_count = 0;
	}
	me->set_temp("check_gold_tick" , tick_count);

	inv = deep_inventory(me);
	if( sizeof(inv) > 35 || me->over_encumbranced()) {
		i = random(sizeof(inv));
		if (inv[i]->query_autoload()) return;
		if (inv[i]->is_character()) return;
		if (inv[i]->query("equipped")) return;
		tell_object(me,
			"你突然发现一"+inv[i]->query("unit") + inv[i]->name() + "不见了！看来是东西太多了。\n"
		);
		destruct(inv[i]);
	}
	inv -= ({ 0 });
	if( environment(me)->query("no_fight") &&
	(me->query("combat_exp") < random(1000000) || me->query_idle( me ) > 120)){
		if(!i = sizeof(inv = filter_array(inv,(:get_object:), me))) return;
		me->add_temp("inv_check", 1);
		if( me->query_temp("inv_check") < 4 ) return;
		if( random(10) < i ){
			i = random(i);
			tell_object(me, "你突然发现身上的一"+inv[i]->query("unit") + inv[i]->name() + "不见了！\n");
			if((string)inv[i]->query("equipped")) inv[i]->unequip();
			destruct(inv[i]);
			me->delete_temp("inv_check");
		}
	}
}
