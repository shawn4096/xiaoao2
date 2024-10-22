//tangfeng@SJ 
//story纪录
//add 连城诀 by tangfeng 2004/11/1
//add 射雕英雄传 by redhat@Sjmud 2009/4/8

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);
string get_string(string str);

//feihu
string quest_feihu(object me); 
string feihu_skill(object me);
//tlbb
string quest_tlbb(object me); 
string tlbb_skill(object me); 
//lchj
string quest_lchj(object me); 
string lchj_skill(object me); 
//shediao
string quest_shediao(object me); 
string shediao_skill(object me); 
//yitian
string quest_yitian(object me); 
string yitian_skill(object me); 

int main(object me, string arg)
{
	object ob;
	string arg1,arg2,str;
	int i_all=0,i_feihu=0,i_tlbb=0,i_lchj=0,i_shediao=0,i_yitian=0;

	str="\n";
	if (!arg)
	{
		ob = me;
		i_all=1;
	}
	else if (sscanf(arg, "%s form %s", arg1,arg2)) 
	{     
		switch (arg1)
		{
		case "feihu" : i_feihu=1;break;
		case "tlbb"  : i_tlbb=1;break;
		case "lchj"  : i_lchj=1;break;//连城诀
		case "shediao"  : i_shediao=1;break;//射雕英雄传
		case "yitian"  : i_yitian=1;break;//倚天屠龙记

		default :
			return notify_fail("目前只开放雪山飞狐、天龙八部、连城诀、射雕英雄传和倚天屠龙记。详细内容请查阅帮助。\n");
		}
		if (wizardp(me))
		{
			ob = present(arg2, environment(me));
			if (!ob) ob = LOGIN_D->find_body(arg2);
			if (!ob) ob = find_living(arg2);
			if (!ob || !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
		} 
		else
			return notify_fail("只有巫师能察看别人的状态。\n");
	}
	else
	{
        ob = me;
		switch (arg)
		{
		    case "feihu" : i_feihu=1;break;
		    case "tlbb"  : i_tlbb=1;break;
			case "lchj"  : i_lchj=1;break;//连城诀
			case "shediao"  : i_shediao=1;break;//射雕英雄传
			case "yitian"  : i_yitian=1;break;//射雕英雄传

			default :
				if (wizardp(me))
				{
					ob = present(arg, environment(me));
					if (!ob) ob = LOGIN_D->find_body(arg);
					if (!ob) ob = find_living(arg);
					if (!ob || !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
					i_all=1;
				} 
				else
					return notify_fail("目前只开放雪山飞狐、天龙八部、连城诀、射雕英雄传和倚天屠龙记。详细内容请查阅帮助。\n");
		}
	}


	if (!wizardp(me) && me->is_busy())
		return notify_fail("你正忙着呢。\n");
	
	if(wizardp(me) && userp(ob)&& me!=ob)
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		str +=get_string(YEL"【你正在查询"+ob->query("name")+"的纪录】"NOR);
	    tell_object(me,str);
	}

	if(i_all==1)  
	{
        str =  "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIY"【书剑秘密全纪录】"NOR);
		str += "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(ob->query("mana")||wizardp(me))
		{   
			str +=sprintf("%30s",HIG"姓名：")+ob->query("name");
			str +="\n";
			str +=sprintf("%30s",HIG"声望：")+chinese_number(ob->query("mana"))+NOR;
			str +="\n";
		}
		if(wizardp(me) && me->query("id")=="master")
		{
			str +=sprintf("%30s",HIG"富源：")+chinese_number(ob->query_kar())+NOR;
			str +="\n";
			str +=sprintf("%30s",HIG"悟性：")+chinese_number(ob->query_int())+NOR;
			str +="\n";
		}
		str += quest_feihu(ob);
		str += quest_tlbb(ob);
		str += quest_lchj(ob);
		str += quest_shediao(ob);
		str += quest_yitian(ob);
	}
	else if(i_feihu==1)        
		str = quest_feihu(ob);
	else if(i_tlbb==1)
		str = quest_tlbb(ob);
	else if(i_lchj==1)
		str = quest_lchj(ob);
	else if(i_shediao==1)
		str = quest_shediao(ob);
	else if(i_yitian==1)
		str = quest_yitian(ob);

	else return notify_fail("目前只开放雪山飞狐、天龙八部、连城诀、射雕英雄传和倚天屠龙记。详细内容请查阅帮助。\n");

    str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	tell_object(me,str);
	return 1;
}


string quest_feihu(object me)
{
	string str= "\n";
	if(!me) return "BUG。\n";
	if(!me->query("quest/雪山飞狐"))
	{
        str =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIW"【目前关于雪山飞狐，没有任何纪录】"NOR);
		return str;
	}

	str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIW"【雪山飞狐】"NOR);
	str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    if(me->query("quest/雪山飞狐/time"))
	{
		if(!me->query("quest/雪山飞狐/解药篇/over") )
			str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-me->query("quest/雪山飞狐/time"))+"。"NOR);
		else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(me->query("quest/雪山飞狐/time"),1)+"。"NOR);
	}
	if(me->query("quest/雪山飞狐/combat_exp"))
	{
			if(!me->query("quest/雪山飞狐/解药篇/over") )
				str +=get_string(WHT"游戏纪录经验差："+chinese_number(me->query("combat_exp")-me->query("quest/雪山飞狐/combat_exp"))+"。"NOR);
			else str +=get_string(WHT"游戏纪录经验："+me->query("quest/雪山飞狐/combat_exp")+"。"NOR);
			str +="\n";
	}
	if(!me->query("quest/雪山飞狐/两页刀法篇"))
	{
		str +=get_string(HBRED"游戏纪录混乱。你还需要努力。"NOR);
		str +=feihu_skill(me);
		return str;
	}
	if(!me->query("quest/雪山飞狐/两页刀法篇/over"))
	{
		if(random(2)) str +=get_string(HBRED"下一步，如何帮助胡斐进一步完善胡家刀法。"NOR);
		else str +=get_string(HBRED"下一步探索：如何寻找失落的最后两页刀法。"NOR);
		str +=feihu_skill(me);
		return str;
	}

	str +=get_string(YEL"你已经帮助胡斐完善胡家刀法，获得一些奖励。"NOR);
	
	if(!me->query("quest/雪山飞狐/复仇篇"))
	{
		if(random(2)) str +=get_string(HBRED"从阎基处你获得过一些旧事，下一步：辨真假。"NOR);
		else          str +=get_string(HBRED"凶手是苗人凤吗？下一步：闯苗家庄。"NOR);
		str +=feihu_skill(me);
		return str;
	}
	
	if(!me->query("quest/雪山飞狐/复仇篇/over"))
	{
		if(random(2)) str +=get_string(HBRED"当年苗、胡之争，似乎已经明了，只是果真如此吗？"NOR);
		else          str +=get_string(HBRED"看来仇人已经明了，只是真正的凶手真的是苗人风吗？"NOR);
		str +=feihu_skill(me);
		return str;
	}   
	str +=get_string(YEL"你已经还原给苗人风和胡斐一个真相，获得一些奖励。"NOR);
	
	if(!me->query("quest/雪山飞狐/解药篇"))
	{
		if(random(2)) str +=get_string(HBRED"但是受小人暗算，苗人风中毒生死未明。"NOR);
		else          str +=get_string(HBRED"20年前的旧事已经明了，复仇之说也算一个完结。"NOR);
		str +=feihu_skill(me);
		return str;
	}
	
	if(!me->query("quest/雪山飞狐/解药篇/over"))
	{
		if(random(2)) str +=get_string(HBRED"真相已经明了，而苗人风中毒生死未明。下一步：寻找解药。"NOR);
		else          str +=get_string(HBRED"20年前的往事已经明了，目前关键是如何寻找治疗苗人风的解药。"NOR);
		str +=feihu_skill(me);
		return str;
	}

	str +=get_string(YEL"五毒教，你成功帮助程灵素夺得七星海棠。"NOR);
	str +=get_string(YEL"药王谷，你成功地炼制解药成功，获得一些奖励。"NOR);
	
	if(!me->query("quest/雪山飞狐/宝藏"))
	{
		str +=get_string(HBRED"你已经完成雪山飞狐的基本情节，最后涉及到一个宝藏。"NOR);
		str +=feihu_skill(me);
		return str;
	}

	str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIB"【闯王宝藏】"NOR);
	str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	if(me->query("quest/雪山飞狐/宝藏/time"))
		str +=get_string(WHT"寻宝纪录时间："+CHINESE_D->chinese_date(me->query("quest/雪山飞狐/宝藏/time"),1)+"。"NOR);
	if(me->query("quest/雪山飞狐/宝藏/combat_exp"))
	{
		str +=get_string(WHT"寻宝纪录经验："+me->query("quest/雪山飞狐/宝藏/combat_exp")+"。"NOR);
		str +="\n";
	}
	if(!me->query("quest/雪山飞狐/宝藏/start"))
	{
		str +=get_string(HBRED"你正在寻找传说中的闯王宝藏。"NOR);
		str +=feihu_skill(me);
		return str;
	}

	str +=get_string(YEL"你已经开始寻找传说中的闯王宝藏。"NOR);
	if(me->query("quest/雪山飞狐/宝藏/jinku"))
		str +=get_string(YEL"你已经从闯王宝藏获得大量的财宝，包括黄金等等。"NOR);
	if(me->query("quest/雪山飞狐/宝藏/yaoku"))
		str +=get_string(YEL"你发现了闯王药库，并在药库获得增长内力的神奇灵药。"NOR);
	if(me->query("quest/雪山飞狐/宝藏/bingqiku"))
		str +=get_string(YEL"你已经挖掘出闯王兵器库的宝物，获得"+chinese_number(me->query("quest/雪山飞狐/宝藏/bingqiku"))+"个宝玉。"NOR);
	if(me->query("quest/雪山飞狐/宝藏/shuku"))
		str +=get_string(YEL"你从书房发现到一个密室，并在这里寻找到增长经验的神奇灵药。"NOR);
	if(me->query("quest/雪山飞狐/武功/lengquanshengong"))
		str +=get_string(YEL"你竟然从一颗灵药里找到一个纸团，并发现冷泉神功秘籍的地点。"NOR);
	else if(me->query("quest/雪山飞狐/宝藏/shuku")>=3)
		str +=get_string(YEL"你从一颗灵药里找到一个似乎是修炼武功的纸团，目前只是未得要领。"NOR);
	str +=feihu_skill(me);
	return str;
}
string feihu_skill(object me)
{
	string str= "";
	if(!me) return "BUG。\n";
	if(me->query("quest/雪山飞狐/两页刀法篇/over"))
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIC"【飞狐武功】"NOR);
        str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(me->query("quest/雪山飞狐/武功/time"))
			str +=get_string(WHT"武功纪录时间："+CHINESE_D->chinese_date(me->query("quest/雪山飞狐/武功/time"),1)+"。"NOR);
		if(me->query("quest/雪山飞狐/武功/combat_exp"))
		{
			str +=get_string(WHT"武功纪录经验："+me->query("quest/雪山飞狐/武功/combat_exp")+"。"NOR);
			str +="\n";
		}
		if(me->query("quest/雪山飞狐/武功/fight_hu"))
		{
		   if(me->query("quest/雪山飞狐/武功/win_hu"))
			   str +=get_string(HIC"你曾与胡斐进行过"+chinese_number(me->query("quest/雪山飞狐/武功/fight_hu"))+"次较量，并获得"+chinese_number(me->query("quest/雪山飞狐/武功/win_hu"))+"次胜利。"NOR);
		   else
			   str +=get_string(HIC"你曾与胡斐进行过"+chinese_number(me->query("quest/雪山飞狐/武功/fight_hu"))+"次较量，可惜一次也没有胜出。"NOR);
		}

		if(me->query("quest/雪山飞狐/武功/hujiadaofa"))
		   str +=get_string(HBYEL"你已经学到了胡家刀法，这门刀法令你的江湖威名大增。"NOR);
		else if(me->query("quest/雪山飞狐/武功/hujiadaofa_fail")>=3 && me->query("registered")<3)
			str +=get_string(YEL"你失去了学习胡家刀法的机会，但如果参入VIP，你将获得新的机会。"NOR);
		else if(me->query("quest/雪山飞狐/武功/hujiadaofa_fail") && me->query("quest/雪山飞狐/武功/hujiadaofa_fail")<3 && me->query("registered")<3)
			str +=get_string(YEL"你失去了学习胡家刀法的"+chinese_number(me->query("quest/雪山飞狐/武功/hujiadaofa_fail"))+"次机会，但你还有"+chinese_number(3-me->query("quest/雪山飞狐/武功/hujiadaofa_fail"))+"机会。"NOR);
		else if(me->query("quest/雪山飞狐/武功/hujiadaofa_fail"))
			str +=get_string(YEL"你失去了学习胡家刀法的"+chinese_number(me->query("quest/雪山飞狐/武功/hujiadaofa_fail"))+"次机会，但你还有无限机会。"NOR);
		else
			str +=get_string(HBRED"你现在拥有学习胡家刀法的机会。你可以在适当的时候请教胡斐。"NOR);
       
	   if(me->query("quest/雪山飞狐/解药篇/over"))
	   {
		   if(me->query("quest/雪山飞狐/武功/fight_miao"))
		   {
			   if(me->query("quest/雪山飞狐/武功/win_miao"))
				   str +=get_string(HIC"你曾与苗人凤进行过"+chinese_number(me->query("quest/雪山飞狐/武功/fight_miao"))+"次较量，并获得"+chinese_number(me->query("quest/雪山飞狐/武功/win_miao"))+"次胜利。"NOR);
			   else str +=get_string(HIC"你曾与苗人凤进行过"+chinese_number(me->query("quest/雪山飞狐/武功/fight_miao"))+"次较量，可惜一次也没有胜出。"NOR);
		   }
		   if(me->query("quest/雪山飞狐/武功/miaojiajianfa"))
			   str +=get_string(HBYEL"你已经学到了苗家剑法，很明显这门剑法对你行走江湖帮助很大。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/miaojiajianfa_fail")>=3 && me->query("registered")<3)
			   str +=get_string(YEL"你浪费了学习苗家剑法的机会，但如果参入VIP，你将获得新的机会。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/miaojiajianfa_fail") && me->query("quest/雪山飞狐/武功/miaojiajianfa_fail")<3 && me->query("registered")<3)
			   str +=get_string(YEL"你失去了学习苗家剑法的"+chinese_number(me->query("quest/雪山飞狐/武功/miaojiajianfa_fail"))+"次机会，但你还有"+chinese_number(3-me->query("quest/雪山飞狐/武功/miaojiajianfa_fail"))+"机会。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/miaojiajianfa_fail"))
			   str +=get_string(YEL"你失去了学习苗家剑法的"+chinese_number(me->query("quest/雪山飞狐/武功/miaojiajianfa_fail"))+"次机会，但你还有无限机会。"NOR);
		   else str +=get_string(HBRED"你现在拥有学习苗家剑法的机会。你可以在适当的时候请教苗人风。"NOR);

		   if(me->query("quest/雪山飞狐/武功/lengquanshengong_teach"))
			   str +=get_string(HBYEL"你已经发现苗、胡上代的秘密，并从苗人凤处领悟到冷泉神功。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/lengquanshengong"))
			   str +=get_string(YEL"你似乎马上要获得冷泉神功的领悟机会。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/shuku")<3 )
			   str +=get_string(YEL"你还有学习冷泉神功的机会。神功据说在宝藏之中。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/shuku")==3 )
			   str +=get_string(YEL"你遇到过一次学习冷泉神功的机会。可惜没有成功。"NOR);
		   else if(me->query("quest/雪山飞狐/武功/shuku")>=4 && me->query("registered")>=3)
			   str +=get_string(YEL"你遇到过两次学习冷泉神功的机会。可惜没有成功。"NOR);
	   }
	}
	return str;
}
string quest_lchj(object me)
{
	string str= "\n";
	if(!me) return "BUG。\n";
	if(!me->query("quest/连城诀"))
	{
        str =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIW"【目前关于连城诀，没有任何纪录】"NOR);
		return str;
	}

    str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIW"【连城诀】"NOR);
    str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

	if(me->query("quest/连城诀/time"))
	{
		if(!me->query("quest/连城诀/武馆探密篇/over"))
			str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-me->query("quest/连城诀/time"))+"。"NOR);
		else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(me->query("quest/连城诀/time"),1)+"。"NOR);
	}
	if(me->query("quest/连城诀/combat_exp"))
	{
		if(!me->query("quest/连城诀/武馆探密篇/over") && !me->query("quest/连城诀/武馆探密篇/over"))
		{
			if(me->query("combat_exp")> me->query("quest/连城诀/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差："+chinese_number(me->query("combat_exp")-me->query("quest/连城诀/combat_exp"))+"。"NOR);
			else if(me->query("combat_exp")== me->query("quest/连城诀/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
			else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(me->query("quest/连城诀/combat_exp")-me->query("combat_exp"))+"。"NOR);
		}
		else str +=get_string(WHT"最后游戏纪录经验："+me->query("quest/连城诀/combat_exp")+"。"NOR);
		str +="\n";
	}

	if(!me->query("quest/连城诀/雪谷激斗篇"))
	{
		str +=get_string(HBRED"你正在努力中........"NOR);
		str +=lchj_skill(me);
		return str;
	}
    if(!me->query("quest/连城诀/雪谷激斗篇/over"))
	{
		if(random(2)) str +=get_string(HBRED"提示：解密乌蚕衣，寻找雪谷狄云。"NOR);
		else str +=get_string(HBRED"一段冤案，一段往事，一段惊奇，一段悲情。"NOR);
		str +=lchj_skill(me);
		return str;
	}

	str +=get_string(YEL"你从丁典获得乌蚕衣，并在雪谷得遇狄云。"NOR);

	if(!me->query("quest/连城诀/武馆探密篇/over"))
	{		
		if(random(2)) str +=get_string(HBRED"下一步：密探武馆。也许真相永远将是一个谜。"NOR);
		else          str +=get_string(HBRED"又是传说中的绝世武功和连城财宝，到底真相如何？"NOR);
		str +=lchj_skill(me);
		return str;
	}
	str +=get_string(YEL"你密探武馆，揭开当年冤情，也获得唐诗选辑。"NOR);
	if(me->query("quest/连城诀/武馆探密篇/baozang"))
	{
			str +=get_string(YEL"你发现连城宝藏，并从狄云处得知一切。"NOR);
			str +=get_string(YEL"虽然没有身外之财，你从中还是获得部分经验奖励。"NOR);
		  str +=lchj_skill(me);
		  return str;
	}
	str +=lchj_skill(me);
	return str;
}
string lchj_skill(object me)
{
	string str= "";
	if(!me) return "BUG。\n";
	if(me->query("quest/连城诀/雪谷激斗篇/start"))
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIB"【连城武功】"NOR);
        str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(me->query("quest/连城诀/武功/time"))
			str +=get_string(WHT"武功纪录时间："+CHINESE_D->chinese_date(me->query("quest/连城诀/武功/time"),1)+"。"NOR);
        if(me->query("quest/连城诀/武功/combat_exp"))
		{
			str +=get_string(WHT"武功纪录经验："+me->query("quest/连城诀/武功/combat_exp")+"。"NOR);
			str +="\n";
		}
		if(me->query("quest/连城诀/武功/shenzhao")>=2)
		{
		   str +=get_string(HBYEL"你从丁典学到神照经，并更能灵活使用神照绝技。"NOR);
		   str +=get_string(HBYEL"你又从狄云处获得一些经验，对神照经有着更深层次的领悟。"NOR);
		}	
		else if(me->query("quest/连城诀/武功/shenzhao")==1)
		{
		   str +=get_string(HBYEL"你从丁典学到神照经，并更能灵活使用神照绝技。"NOR);
		   if(me->query("quest/连城诀/雪谷激斗篇/over"))
		   {
			   if(me->query("quest/连城诀/武功/shenzhao_fail2")>=3 && me->query("registered")<3)
			   {
				   str +=get_string(YEL"但是你失去了从狄云处学习神照经更高层次的领悟机会。"NOR);
				   str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
			   }
			   else if(me->query("quest/连城诀/武功/shenzhao_fail2") && me->query("quest/连城诀/武功/shenzhao_fail2") <3 && me->query("registered")<3)
				   str +=get_string(YEL"你失去了狄云处领悟神照经的"+chinese_number(me->query("quest/连城诀/武功/shenzhao_fail2"))+"次机会，但你还有"+chinese_number(3-me->query("quest/连城诀/武功/shenzhao_fail2"))+"机会。"NOR);
			   else if(me->query("quest/连城诀/武功/shenzhao_fail2"))
				   str +=get_string(YEL"你失去了狄云处领悟神照经的"+chinese_number(me->query("quest/连城诀/武功/shenzhao_fail2"))+"次机会，但你还有无限机会。"NOR);
			   else str +=get_string(HBRED"你现在拥有从狄云处领悟更高层次神照经的机会。你可以在适当的时候请教狄云。"NOR);
		   }
		} 
		else if(me->query("quest/连城诀/武功/shenzhao_fail")>=3 && me->query("registered")<3)
			str +=get_string(YEL"你失去从丁典领悟神照经的机会，但如果参入VIP，你将获得新的机会。"NOR);
		else if(me->query("quest/连城诀/武功/shenzhao_fail") && me->query("quest/连城诀/武功/shenzhao_fail")<3 && me->query("registered")<3)
			str +=get_string(YEL"你失去从丁典领悟神照经的"+chinese_number(me->query("quest/连城诀/武功/shenzhao_fail"))+"次机会，但你还有"+chinese_number(3-me->query("quest/连城诀/武功/shenzhao_fail"))+"机会。"NOR);
		else if(me->query("quest/连城诀/武功/shenzhao_fail"))
			str +=get_string(YEL"你失去从丁典领悟神照经的"+chinese_number(me->query("quest/连城诀/武功/shenzhao_fail"))+"次机会，但你还有无限机会。"NOR);
		else str +=get_string(HBRED"你现在拥有领悟神照经的机会。你可以在适当的时候请教丁典。"NOR);
        
		if(me->query("quest/连城诀/雪谷激斗篇/over"))
		{
			if(me->query("quest/连城诀/武功/sword"))
				str +=get_string(HBYEL"你从狄云学习到躺尸剑法，并更能灵活各种绝技。"NOR);
			else if(me->query("quest/连城诀/武功/sword_fail")>=3 && me->query("registered")<3)
			{
				str +=get_string(YEL"但是你失去学习从狄云处躺尸剑法的机会。\n"NOR);
				str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
			}
			else if(me->query("quest/连城诀/武功/sword_fail") && me->query("quest/连城诀/武功/sword_fail") <3 && me->query("registered")<3)
				str +=get_string(YEL"你失去学习躺尸剑法的"+chinese_number(me->query("quest/连城诀/武功/sword_fail"))+"次机会，但你还有"+chinese_number(3-me->query("quest/连城诀/武功/sword_fail"))+"机会。"NOR);
			else if(me->query("quest/连城诀/武功/sword_fail"))
				str +=get_string(YEL"你失去学习躺尸剑法的"+chinese_number(me->query("quest/连城诀/武功/sword_fail"))+"次机会，但你还有无限机会。"NOR);
			else str +=get_string(HBRED"你现在拥有学习躺尸剑法的机会。你可以在适当的时候请教狄云。"NOR);
		}
	}
	return str;
}
string quest_tlbb(object me)
{
	string str= "\n";
	if(!me) return "BUG。\n";
	if(!me->query("quest/天龙八部"))
	{
        str =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIW"【目前关于天龙八部，没有任何纪录】"NOR);
		return str;
	}

    str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIW"【天龙八部】"NOR);
    str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

	if(me->query("quest/天龙八部/time"))
	{
		if(!me->query("quest/天龙八部/复兴天下篇/over") && !me->query("quest/天龙八部/大辽救援篇/over"))
			str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-me->query("quest/天龙八部/time"))+"。"NOR);
		else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(me->query("quest/天龙八部/time"),1)+"。"NOR);
	}
	if(me->query("quest/天龙八部/combat_exp"))
	{
		if(!me->query("quest/天龙八部/复兴天下篇/over") && !me->query("quest/天龙八部/大辽救援篇/over"))
		{
			if(me->query("combat_exp")> me->query("quest/天龙八部/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差："+chinese_number(me->query("combat_exp")-me->query("quest/天龙八部/combat_exp"))+"。"NOR);
			else if(me->query("combat_exp")== me->query("quest/天龙八部/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
			else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(me->query("quest/天龙八部/combat_exp")-me->query("combat_exp"))+"。"NOR);
		}
		else str +=get_string(WHT"最后游戏纪录经验："+me->query("quest/天龙八部/combat_exp")+"。"NOR);
		str +="\n";
	}

	if(!me->query("quest/天龙八部/凌波微步篇"))
	{
		str +=get_string(HBRED"你正在努力中........"NOR);
		str +=tlbb_skill(me);
		return str;
	}
    if(!me->query("quest/天龙八部/凌波微步篇/over"))
	{
		if(!me->query("quest/天龙八部/凌波微步篇/wuliangover"))
		{
			if(random(2)) str +=get_string(HBRED"如何寻找段誉，据说在无量山。正在探索中。"NOR);
			else str +=get_string(HBRED"寻找失踪的段誉中，注意别忘记随便解密凌波微步和北溟神功。"NOR);
		}
		else
		{
			if(random(2)) str +=get_string(HBRED"从无量山回来的段誉却被劫持到万劫谷。正在探索中。"NOR);
			else str +=get_string(HBRED"寻找失踪的段誉中，注意小心有高手阻截。"NOR);
		}
		return str;
	}

	str +=get_string(YEL"你已经将段誉从万劫谷救回，并获得一些奖励。"NOR);

	if(!me->query("quest/天龙八部/天龙营救篇/over"))
	{		
		if(random(2)) str +=get_string(HBRED"下一步：天龙寺大战。倒霉的段誉又牵涉其中，当然只有你来帮忙。"NOR);
		else          str +=get_string(HBRED"西夏第一佛法高僧，武功也是深不可测，能阻止他的只有你了。"NOR);
		str +=tlbb_skill(me);
		return str;
	}

	str +=get_string(YEL"你阻大轮高手于殿外，救段誉于西夏，并获得一些奖励。"NOR);

	if(!me->query("quest/天龙八部/萧峰身世篇/over"))
	{
		if(random(2)) str +=get_string(HBRED"谁是小人，谁是英雄，中原旧事，究竟多少秘密被湮灭。"NOR);
		else          str +=get_string(HBRED"竹林惊变，聚闲庄大战，颂摩崖遗魂，历史还我真相..."NOR);
		str +=tlbb_skill(me);
		return str;
	}
	str +=get_string(YEL"聚闲庄，你解救了萧峰成功脱离现场；"NOR);
	str +=get_string(YEL"颂摩崖，你成功揭开崖壁遗书的秘密。"NOR);
	if(me->query("quest/天龙八部/萧峰身世篇/good"))
		str +=get_string(YEL"你更是成功说服了萧峰归隐江湖，获得部分奖励。"NOR);
	if(me->query("quest/天龙八部/萧峰身世篇/bad"))
		str +=get_string(YEL"你更是成功了击退了契丹人萧峰，获得部分奖励。"NOR);

	if(me->query("quest/天龙八部/复兴天下篇/start"))
	{
		if(!me->query("quest/天龙八部/复兴天下篇/over"))
			str +=get_string(HBRED"为独霸武林，联手慕容，江湖上，毕竟还是得看拳头的。"NOR);
		else 
			str +=get_string(YEL"你独闯少林大败群丐，击退无名神僧与萧峰联手，为天下第一。"NOR);
		str +=tlbb_skill(me);
		return str;
	}
	if(me->query("quest/天龙八部/大辽救援篇/start"))
	{
		if(!me->query("quest/天龙八部/大辽救援篇/over"))
			str +=get_string(HBRED"萧峰为百姓找想，誓不战争，此人当要救的。只是危险重重。"NOR);
		else 
			str +=get_string(YEL"你完胜中原群雄，并潜入大辽，成功营救萧峰，为侠义豪杰。"NOR);
		str +=tlbb_skill(me);
		return str;
	}
	str +=tlbb_skill(me);
	return str;
}
string tlbb_skill(object me)
{
	string str= "";
	if(!me) return "BUG。\n";
	if(me->query("quest/天龙八部/武功"))
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIC"【天龙武功】"NOR);
        str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(me->query("quest/天龙八部/武功/time"))
			str +=get_string(WHT"最后学习纪录时间："+CHINESE_D->chinese_date(me->query("quest/天龙八部/武功/time"),1)+"。"NOR);
        if(me->query("quest/天龙八部/武功/combat_exp"))
		{
			str +=get_string(WHT"最后学习纪录经验："+me->query("quest/天龙八部/武功/combat_exp")+"。"NOR);
			str +="\n";
		}
		if(me->query("quest/天龙八部/武功/yuxiang"))
		{            
			if(me->query("quest/天龙八部/凌波微步篇/over"))
				str +=get_string(YEL"你找到MM的玉像，并获得一些提示。你获得记载凌波微步的帛卷。"NOR);
			else
				str +=get_string(YEL"你找到MM的玉像，并获得一些提示。"NOR);
		}
		if(me->query("quest/天龙八部/北冥神功/pass"))
			str +=get_string(HBYEL"在无量山洞中你已经学到了北冥神功绝学。"NOR);
		else if(me->query("quest/天龙八部/北冥神功/fail")>=3 && me->query("registered")<3)
		{
			str +=get_string(YEL"但是你浪费了学习北冥神功的机会。"NOR);
			str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
		}
		else if(me->query("quest/天龙八部/北冥神功/fail"))
		{
			str +=get_string(YEL"但是你失去了学习北冥神功的"+chinese_number(me->query("quest/天龙八部/北冥神功/fail"))+"次机会。"NOR);
			str +=get_string(YEL"但你还有机会学习，新的帛卷可以从玉像处重新获得。"NOR);
		}
		else str +=get_string(HBRED"你现在拥有学习北冥神功的机会。"NOR);
	
		if(me->query("quest/天龙八部/武功/pass"))
			str +=get_string(HBYEL"并从中已经学到了凌波微步。"NOR);
		else if(me->query("quest/天龙八部/武功/fail")>=3 && me->query("registered")<3)
		{
			str +=get_string(YEL"但是你浪费了学习凌波微步的机会。"NOR);
			str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
		}
		else if(me->query("quest/天龙八部/武功/fail"))
		{
			str +=get_string(YEL"但是你失去了学习凌波微步的"+chinese_number(me->query("quest/天龙八部/武功/fail"))+"次机会。"NOR);
			str +=get_string(YEL"但你还有机会学习，新的帛卷可以从玉像处重新获得。"NOR);
		}
		else str +=get_string(HBRED"你现在拥有学习凌波微步的机会。"NOR);
	}
	if(me->query("quest/tonglao/quest"))
	{
		if(me->query("quest/tonglao/pass"))
			str +=get_string(YEL"你曾"+chinese_number(me->query("quest/tonglao/quest"))+"次见到天山灯火，偶救天山童姥，并学到绝世武功。"NOR);
		else if(me->query("quest/tonglao/second"))
			str +=get_string(YEL"你曾"+chinese_number(me->query("quest/tonglao/quest"))+"次见到天山灯火，偶救天山童姥。"NOR); 
		else str +=get_string(YEL"你曾"+chinese_number(me->query("quest/tonglao/quest"))+"次见到天山灯火，但什么也没发现。"NOR);
	}

	if(me->query("quest/天龙八部/武功/quanli"))
		str +=get_string(HBYEL"你从萧峰那里领悟到“返璞归真”的武功真谛。"NOR);
	return str;
}

string quest_shediao(object me)
{
	string str= "\n";
	if(!me) return "BUG。\n";
	if(!me->query("quest/射雕英雄传"))
	{
        str =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIW"【目前关于射雕英雄传，没有任何纪录】"NOR);
		return str;
	}

    str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIW"【射雕英雄传】"NOR);
    str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
//对比时间
	if(me->query("quest/射雕英雄传/time"))
	{
		if(!me->query("quest/射雕英雄传/风雪惊变/over") )
			str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-me->query("quest/射雕英雄传/time"))+"。"NOR);
		else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(me->query("quest/射雕英雄传/time"),1)+"。"NOR);
	}

//对比经验
	if(me->query("quest/射雕英雄传/combat_exp"))
	{
		if(!me->query("quest/射雕英雄传/风雪惊变/over") )
		{
			if(me->query("combat_exp")> me->query("quest/射雕英雄传/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差："+chinese_number(me->query("combat_exp")-me->query("quest/射雕英雄传/combat_exp"))+"。"NOR);
			else if(me->query("combat_exp")== me->query("quest/射雕英雄传/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
			else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(me->query("quest/射雕英雄传/combat_exp")-me->query("combat_exp"))+"。"NOR);
				str +=get_string(HIC"你已经成功救下杨铁心，但郭啸天不幸遇难，并获得一些奖励。"NOR);
		}
		else str +=get_string(WHT"最后游戏纪录经验："+me->query("quest/射雕英雄传/combat_exp")+"。"NOR);
		str +="\n";
	}
//判断故事情节进度
//第一章节
	if (!me->query("quest/射雕英雄传/风雪惊变/over"))
	{
		if (me->query("quest/射雕英雄传/风雪惊变/成功保护杨铁心"))
		{
			str +=get_string(CYN"你成功从宋兵手中救下杨铁心，但不幸的是郭啸天为宋兵所杀。"NOR);
			
		}else if (me->query("quest/射雕英雄传/tongyin"))
		{
			str +=get_string(CYN"通过在杨铁心家中痛饮，一醉方休，彼此成为生死好友。"NOR);
		}else if (me->query("quest/射雕英雄传/notongyin")&& me->query("quest/射雕英雄传/bad"))
		{
			str +=get_string(CYN"不屑于与这些草民为伍，你选择了去保护大金国王爷完颜洪烈。"NOR);
		}
		else if (me->query("quest/射雕英雄传/风雪惊变/xiangzhi"))
		{
			str +=get_string(CYN"虽然和丘处机发生小冲突，但误会尽去，彼此惺惺相惜。"NOR);
		}
		else str +=get_string(CYN"游戏情节在进行中。"NOR);
	}else {

		str +=get_string(YEL"成功解救杨铁心，郭啸天被敌人所杀，李萍为段天德所掳走。"NOR);
		if (!me->query("quest/射雕英雄传/江南七怪/start"))
			str +=get_string(HBRED"下一步如何处理，你需将此事告知丘处机道长。"NOR);
	}

	//第二章节
	if (!me->query("quest/射雕英雄传/江南七怪/over"))
	{
		if (me->query("quest/射雕英雄传/江南七怪/dadu"))
		{
			str +=get_string(CYN"你和江南七怪打赌，相约十八年后嘉兴烟雨楼比武。"NOR);
			
		}else if (me->query("quest/射雕英雄传/江南七怪/法华寺激战"))
		{
			str +=get_string(CYN"你与江南七怪在法华寺一场大战，焦木撞墙而亡，彼此间惺惺相惜。"NOR);
		}else if (me->query("quest/射雕英雄传/烟雨楼成功杀死金兵"))
		{
			str +=get_string(CYN"烟雨楼中和江南七怪斗酒，不分伯仲。"NOR);
		}
		else if (me->query("quest/射雕英雄传/江南七怪/敬酒完成"))
		{
			str +=get_string(CYN"在嘉兴烟雨楼中和江南七怪依次敬酒，大有相见恨晚之意。"NOR);
		}
		else str +=get_string(CYN"游戏情节在进行中。"NOR);
	}else {

		str +=get_string(YEL"和江南七怪达成赌约，约好十八年后嘉兴烟雨楼比武定输赢。"NOR);
		if (!me->query("quest/射雕英雄传/大漠风沙/start"))
			str +=get_string(HBRED"下一步如何处理，你需到大漠去一趟，也许能如你所愿。"NOR);
	}
	
	str +=shediao_skill(me);
	return str;
}
//射雕英雄传武功
string shediao_skill(object me)
{
	string str= "";
	if(!me) return "BUG。\n";
	if(me->query("quest/射雕英雄传/yangjiaqiang"))
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIC"【射雕武功】"NOR);
        str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(me->query("quest/射雕英雄传/yangjiaqiang/time"))
			str +=get_string(WHT"最后学习纪录时间："+CHINESE_D->chinese_date(me->query("quest/射雕英雄传/yangjiaqiang/time"),1)+"。"NOR);
        if(me->query("quest/射雕英雄传/yangjiaqiang/combat_exp"))
		{
			str +=get_string(WHT"最后学习纪录经验："+me->query("quest/射雕英雄传/yangjiaqiang/combat_exp")+"。"NOR);
			str +="\n";
		}
		if(me->query("quest/射雕英雄传/风雪惊变/over"))
		{            
				str +=get_string(YEL"你成功救援郭啸天、杨铁心两家，并获得一些奖励。"NOR);
		}
		if(me->query("quest/射雕英雄传/yangjiaqiang/pass"))
			str +=get_string(HBYEL"并从中已经学到了杨家枪。"NOR);
		else if(me->query("quest/射雕英雄传/yangjiaqiang/fail")>=3 && me->query("registered")<3)
		{
			str +=get_string(YEL"但是你浪费了学习杨家枪的机会。"NOR);
			str +=get_string(YEL"当然，如果你参入VIP，你将获得新的学习机会。"NOR);
		}
		else if(me->query("quest/射雕英雄传/yangjiaqiang/fail"))
		{
			str +=get_string(YEL"但是你失去了学习杨家枪的"+chinese_number(me->query("quest/射雕英雄传/yangjiaqiang/fail"))+"次机会。"NOR);
			str +=get_string(YEL"但你还有机会学习，在适当的时候可以去寻找杨铁心请教。"NOR);
		}
		else str +=get_string(HBRED"你现在拥有学习杨家枪的机会。"NOR);
	}
	if(me->query("quest/jiuyin1/pass"))
		str +=get_string(HBYEL"你从周伯通处获得了闻名天下九阴真经上卷。"NOR);
	if(me->query("quest/jiuyin2/pass"))
		str +=get_string(HBYEL"你从陈玄风处获得了臭名昭著九阴真经下卷。"NOR);
	return str;
}

string quest_yitian(object me)
{
	
	string str= "\n";
	if(!me) return "BUG。\n";
	if(!me->query("quest/倚天屠龙记"))
	{
        str =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIW"【目前关于倚天屠龙记，没有任何纪录】"NOR);
		return str;
	}

    str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	str +=get_string(HIW"【倚天屠龙记】"NOR);
    str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

	if(me->query("quest/倚天屠龙记/time"))
	{
		if(!me->query("quest/倚天屠龙记/华山之巅/over") )
			str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-me->query("quest/倚天屠龙记/time"))+"。"NOR);
		else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(me->query("quest/倚天屠龙记/time"),1)+"。"NOR);
	}
	/*
	if(me->query("quest/倚天屠龙记/combat_exp"))
	{
		if(!me->query("quest/倚天屠龙记/华山之巅/over") )
		{
			if(me->query("combat_exp")> me->query("quest/倚天屠龙记/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差："+chinese_number(me->query("combat_exp")-me->query("quest/倚天屠龙记/combat_exp"))+"。"NOR);
			else if(me->query("combat_exp")== me->query("quest/倚天屠龙记/combat_exp"))
				str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
			else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(me->query("quest/倚天屠龙记/combat_exp")-me->query("combat_exp"))+"。"NOR);
				str +=get_string(HIC"你已经成功阻击尹克西和潇湘子的偷袭，并发现这二人并未携带没有任何经书。"NOR);
		}
		else str +=get_string(WHT"最后游戏纪录经验："+me->query("quest/倚天屠龙/combat_exp")+"。"NOR);
		str +="\n";
	}
	else
		{

} */

	str +=yitian_skill(me);
	return str; 
}

string yitian_skill(object me)
{
	string str= "";
	if(!me) return "BUG。\n";
	if(me->query("quest/倚天屠龙记/"))
	{
        str =   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	    str +=get_string(HIC"【倚天武功】"NOR);
        str +=   "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		if(me->query("quest/倚天屠龙记/time"))
			str +=get_string(WHT"最后学习纪录时间："+CHINESE_D->chinese_date(me->query("quest/倚天屠龙记/time"),1)+"。"NOR);
        if(me->query("quest/倚天屠龙记/combat_exp"))
		{
			str +=get_string(WHT"最后学习纪录经验："+me->query("quest/倚天屠龙记/combat_exp")+"。"NOR);
			str +="\n";
		}
		
		if (me->query("was_job/wasscore"))
		{
			str +=get_string(WHT"万安寺积分："+me->query("was_job/wasscore")+"点"NOR);
			str +="\n";
		}
		if (me->query("gmd_job/gmdscore"))
		{
			str +=get_string(WHT"光明顶积分："+me->query("gmd_job/gmdscore")+"点"NOR);
			str +="\n";
		}
		
		if(me->query("quest/倚天屠龙记/华山之巅/over"))
		{            
				str +=get_string(YEL"你成功阻拦尹克西和潇湘子的逃窜并从二人身上得知一句话。"NOR);
		}
		
		if(me->query("quest/倚天屠龙记/was/pass"))
		{            
				str +=get_string(YEL"你成功从万安寺解救群雄并得知经书下落。"NOR);
		}
		
		if(me->query("quest/倚天屠龙记/tiaoya/pass"))
			str +=get_string(HBYEL"并已经成功跳入山谷。"NOR);
		else if(me->query("quest/倚天屠龙记/tiaoya/fail")>=3 && me->query("registered")<3)
		{
			str +=get_string(YEL"但是你浪费了学习《九阳真经》的机会。"NOR);
			str +=get_string(YEL"当然，如果你参入VIP，你将获得新的学习机会。"NOR);
		}
		else if(me->query("quest/倚天屠龙记/tiaoya/fail"))
		{
			str +=get_string(YEL"但是你失去了学习九阳真经的"+chinese_number(me->query("quest/倚天屠龙记/tiaoya/fail"))+"次机会。"NOR);
			str +=get_string(YEL"但你还有机会学习，在适当的时候可以去寻找机缘。"NOR);
		}
		else str +=get_string(HBRED"你现在拥有发现九阳真经奥秘的机会。"NOR);
		
		if(me->query("quest/倚天屠龙记/jiuyangzhenjing/pass"))
		{            
				str +=get_string(YEL"你成功学到了武林绝学《九阳真经》。"NOR);
		}
	}
//玄冥神掌、幻阴指、大力金刚指
//	if(me->query("quest/jiuyin1/pass"))
		//str +=get_string(HBYEL"你从周伯通处获得了闻名天下九阴真经上卷。"NOR);
	//if(me->query("quest/jiuyin2/pass"))
		//str +=get_string(HBYEL"你从陈玄风处获得了臭名昭著九阴真经下卷。"NOR);
	return str;
} 

string get_string(string str)
{
     return sprintf("%|60s",str)+"\n";
}
int help(object me)
{
	write("
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
             指令格式 : "+YEL"story <......>"NOR"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"HIW"这个命令可以让你很清楚地了解你story已经揭开的程度。你也可以使
用这个命令得到一点下一步的提示。"NOR"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"YEL"
                story  获得所有纪录
          story feihu  获得雪山飞狐纪录
           story tlbb  获得天龙八部记录
           story lchj  获得连城诀记录
         story <玩家>  巫师专用查询命令
 story ...<form 玩家>  巫师专用查询命令"NOR"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
          "HIC"目前只开放雪山飞狐、天龙八部和连城诀。"NOR"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
		  \n"NOR);
return 1;
}
