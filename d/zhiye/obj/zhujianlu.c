// zhujianlu.c
// by augx@sj 9/6/2001
// modified by Ciwei@SJ

#include <ansi.h>
#include <job_mul.h>
inherit ITEM;

string long();
int check(object me);
int duanzao_it(object me,string arg);

void create()
{
        set_name(HIR"火炉"NOR, ({ "huo lu" , "lu" }));
        set_weight(1000000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long",(:long:) );
                set("value", 3000);
                set("no_get", 1);
        }
        setup();
       /*
       改名(gaiming): gaiming 新名字 兵器id
注意：
    1.不要加上种类名字如『剑』『刀』之类，系统会自动加上！
    2.武器ID会变成你的 ID + 武器 ID。
    3.你可以使用 $颜色$ 字串加上颜色，颜色说明见help color。
    4.名字的最后不需要加 $NOR$ 字串，系统会自动添加。
    5.请勿使用不雅观的名字命名，否则巫师有权利收回你的兵器。
    6.请使用中文命名，否则巫师有权利收回你的兵器。
    */
}

string long()
{
	string str;
	object me;
			
str = HIR"这是一座日夜炉火通明的火炉，和普通打铁铺的火炉并不相同。
此炉以特殊材料制成，能耐无法想像的高温，是专门用来锻造兵器的！\n\n"NOR+
"你可以用这个火炉来：

锻造(duanzao)：duanzao 兵器种类 原料 [with 佩宝]
（现在可以锻造的兵器有：sword，xiao，axe，blade，brush，club，
  dagger，fork，hammer，hook，spear，arrow , staff，stick，whip）

修理(xiu):     xiu 兵器id
";
	me = this_player();
	if(!me) return str;
	if(check(me))
		return str+"\n\n铸剑师在一旁向你眨了眨眼。\n";
	return str;
}

int check(object me)
{
	if(!me) return 0;
	//return (me->query("imbue_weapon") && (time()-me->query("imbue_weapon")) <3600);
	return !userp(me);
}

void init()
{
        add_action("do_duanzao","duanzao");
        add_action("do_xiu","xiu");
        add_action("do_xiu","fix");
       // add_action("do_rename","gaiming");
        //add_action("do_rename","rename");
        //add_action("do_recover","restore");
        
        if(inherits(ROOM,environment(this_object()))!=0	) environment(this_object())->set("no_fight",1);
}

int do_duanzao(string arg)
{
        object me = this_player();
        return duanzao_it(me,arg);
}

int duanzao_it(object me,string arg)
{
	object obj,obj2,weapon,fujia;
        int delay,level,i,j,k,time;
        string* status = ({});
        mapping temp;
        float updown;
        //float power;
        string type,kuangcai;
        string jade;//hehe
        mapping myskill;
        mapping shuxing = ([]);
        
	level = (int)me->query_skill("duanzao",1);
        if (!check(me) && me->is_busy()) return notify_fail("你正忙着呢！\n");
        if (!check(me) && me->is_fight()) return notify_fail("你正忙着呢！\n");
        if (!arg) return notify_fail("你要锻造什么？\n");
        if ( sscanf(arg,"%s %s",type,kuangcai)<2 )
                return notify_fail("你要用什么锻造什么？\n");
	
	if(check(me)) level=999;
	
        if(sscanf(kuangcai,"%s with %s",kuangcai,jade)==2)
        {
        	if ( !objectp(fujia = present(jade, me)) )
                return notify_fail("你身上没有这样东西。\n");
                if ( !objectp(obj = present(kuangcai, me)) )
                return notify_fail("你身上没有这样东西。\n");
                
                if(fujia->query("material_for")!="weapon") return notify_fail("你左看右看总觉得"+fujia->name()+"与"+obj->name()+"不合适。\n");
                switch( (int)fujia->query("material_level") ) {
                case 1: break;
                case 2: if(level<120) return notify_fail("你的锻造技能不够！\n"); break;
                case 4: if(level<220) return notify_fail("你的锻造技能不够！\n"); break;
                case 6: if(level<330) return notify_fail("你的锻造技能不够！\n"); break;                
                case 8: if(level<390) return notify_fail("你的锻造技能不够！\n"); break;                
                case 10: if(level<400) return notify_fail("你的锻造技能不够！\n"); break;
        	}
	}
        if ( !objectp(obj = present(kuangcai, me)) )
                return notify_fail("你身上没有这样东西。\n");
        obj = present(obj->query("id"), me);
        if ( !objectp(obj2= present(obj->query("id")+" 2", me)) )
                return notify_fail("你必须用两块"+obj->query("name")+"来锻造兵器。\n");
        if( !(int)obj->query("kuangcai") || !(int)obj->query("level") )
                return notify_fail("在这里只能用从矿石中提炼出来的材料锻造兵器。\n");
        if ( !objectp(weapon=me->query_temp("weapon")) || weapon->query("id")!="tiechui" )
                return notify_fail("你必须装备铁锤才能来锻造。\n");
        if (!check(me) && !weapon->query("worker_tool"))
                return notify_fail("你必须装备铁锤才能来锻造。\n");
        if (!check(me) && !wizardp(me) && (time()<(int)me->query("worker/duanzao")) )
                return notify_fail("你刚刚锻造过兵器，感觉过于劳累！\n");

        time = time()- me->query("pk_time");
        if (!check(me) && time < 4300)
                return notify_fail("你目前的状态无法锻造。\n");	
	                       
        if (!check(me) && level<1 )
                return notify_fail("你根本就不会打造兵器！是不是先学习一些锻造技能(duanzao)再来打造武器啊？！\n");

        switch(type){
                case "sword":
                case "axe":
                case "blade":
                case "brush":
                case "club":
                case "dagger":
                case "fork":
                case "hammer":
                case "hook":
                case "spear":
//                 case "arrow":
                
                case "stick":
				case "staff":
				//case "lun":
				case "xiao":
                case "whip": break;
                default:
                        return notify_fail("这里不能锻造这种武器。\n");
        }
        
        switch( (int)obj->query_level() ) {
                case 1: break;
                case 2: if(level<40)  return notify_fail("你的锻造技能不够！\n"); break;
                case 3: if(level<80)  return notify_fail("你的锻造技能不够！\n"); break;
                case 4: if(level<120) return notify_fail("你的锻造技能不够！\n"); break;
                case 5: if(level<170) return notify_fail("你的锻造技能不够！\n"); break;
                case 6: if(level<220) return notify_fail("你的锻造技能不够！\n"); break;
                case 7: if(level<270) return notify_fail("你的锻造技能不够！\n"); break;
                case 8: if(level<330) return notify_fail("你的锻造技能不够！\n"); break;
                case 9: if(level<390) return notify_fail("你的锻造技能不够！\n"); break;
                case 10: if(level<400) return notify_fail("你的锻造技能不够！\n"); break;
        }
        
        myskill = me->query("forging");//当它Quest了
        
        if (!check(me) && !mapp(myskill)) return notify_fail("你还不会任何工匠技能！\n");
        
	if (!check(me) && member_array(type,keys(myskill)) == -1)
		return notify_fail("对于这种武器，您了解不多，还不会锻造！\n");
	
	if(level>220) k = 10000*level*(int)obj->query_level()/15;
	else k = 10000*level*(int)obj->query_level()/20;
	if(me->query("registered")==3) k = k*2/3;
	if(!check(me) && k>=10000){
		switch(MONEY_D->player_pay(me, k,0,1))
		{
			case 0:return notify_fail("你在钱庄的存款不足支付此次锻造。\n");
			default:write("你为此次锻造支付了"+MONEY_D->money_str(k)+"。\n");
		}
		/*
		if(me->query("balance")<k) return notify_fail("你在钱庄的存款不足支付此次锻造。\n");
		me->add("balance",-k);
		write("你为此次锻造支付了"+MONEY_D->money_str(k)+"。\n");
		*/
	}
	        
        shuxing = WORKER_D->map_add(shuxing,obj->query("material_prop"));
        shuxing = WORKER_D->map_add(shuxing,obj2->query("material_prop"));
        if(objectp(fujia))
        {
        	temp = fujia->query("material_props");
        	if(mapp(temp)) status = copy(values(temp));
        	shuxing = WORKER_D->map_add(shuxing,fujia->query("material_prop"));
        } 
        
        me->delete("imbue_weapon");
        
        message_vision(HIY"$N开始从各个角度锤击"+obj->query("name")+HIY"，一点点把原始的材料变成无双的兵器......\n"NOR, me);
        me->set_temp("pending/duanzao",1);
		level = (int)me->query_skill("duanzao",1);
        if(level>390) level = 390 + (level-390)*11;
        switch((int)obj->query_level()) {
                case 1: i = 40;  if(level>100) level=100;j=0; break;
                case 2: i = 80;  if(level>150) level=150;j=0; break;
                case 3: i = 120;j=0;
                	if(level>200) j +=random(2);
                	if(level>200) level=200;break;
                case 4: i = 170; if(level>300) level=300;j=1; break;
                case 5: i = 800;j=1;
                	if(level>350) j +=random(2);
                	if(level>350) level=350;break;
                case 6: i = 999; if(level>450) level=450;j=2; break;
                case 7: i = 2000;j=2;
                	if(level>440) j +=random(2);
                	if(level>500) level=500;break;
                case 8: i = 3000;if(level>500) level=500;j=3; break;
                case 9: i = 9999;j=3;
                	if(level>500) j +=random(2);
                	if(level>500) level=500;break;
                case 10: i = 20000;if(level>600) level=600;j=4; break;
        }
        if(wizardp(me) && me->query("env/test") && i>500) i=500;

        delay = 1;
        k = random(level+i);        
        
        updown = WORKER_D->updown(me,type);
        //if( objectp(fujia) || ( k>=((level+i)/2-level/2) && k<=((level+i)/2+level/2) ) )  
        if( objectp(fujia) || ( k>=to_int(((level+i)/2-level/4)/updown) && k<=to_int(((level+i)/2+level/4)*updown)  ) ) {
                if(wizardp(me) && (int)me->query("env/test")) delay = 6;
                if (j>=3) {
                        WORKER_D->update_UniqueValues("weapon","","");
                        delay = 1;
                        if(wizardp(me) && (int)me->query("env/test")) delay = 1;
                }
                call_out("duanzao_makeweapon",delay,me,type,j,obj,delay,shuxing,status);//使用了玉打造成功率100% 原来成功率下调
        }
        else {
                if(wizardp(me) && (int)me->query("env/test")) delay = 3;
                call_out("duanzao_finish",delay*2-1,j,me,obj,0);
        }

        me->start_busy(delay+1);
        destruct(obj2);
        if(objectp(fujia)) destruct(fujia);
        return 1;
}

void duanzao_makeweapon(object me,string type,int qua,object obj,int delay,mapping shuxing,string* status)
{
        object wp,shi;
        string str,st;

        if(!objectp(me) || !objectp(obj)) return;
/*
        if( qua>=3 && WORKER_D->query_UniqueValues("weapon","") <0 ) {
                tell_object(me , "网络错误：无法连接同步服务器，你将无法打造高等级兵刃！\n");
                qua = 2;
                delay = 10;
        }
        if( qua==4 && WORKER_D->query_UniqueValues("weapon",me->query("id")) <1 ) {
                tell_object(me , "一级兵刃已经达到限制数，无法打造！\n");
                qua = 2;
                delay = 10;
        }
        if( qua==3 && WORKER_D->query_UniqueValues("weapon2",me->query("id"))<1 ) {
                tell_object(me , "二级兵刃已经达到限制数，无法打造！\n");
                qua = 2;
                delay = 10;
        }
  */      
        wp = WORKER_D->make_weapon(me,type,qua,obj->query("material"),shuxing,status);
        //wp->set("value" , (obj->query("value")*4)/100 * (wp->query("value")/30)/100 );
        wp->set("value" , obj->query("value") * (25+random(40)) / 10 );
        
		wp->set("weapon_mp/value" , wp->query("value"));
        if(!wp) {
                tell_object(me, "武器生成出错! \n");
                return;
        }
        if( !environment(this_object()) || !(shi=present("zhujian shi",environment(this_object()))) ) {
                tell_object(me, "无法找到铸剑师! \n");
                return;
        }
        if(!wp->move(shi)) {
                tell_object(me, "武器移动错误! \n");
                return;
        }
        me->set_temp("worker/wp" , wp);

        if( qua>=3 ) {
                if ( stringp(wp->query("name_st")) && strlen(wp->query("name_st"))>3 )
                        st = wp->query("name_st");
                else
                        st = "";
                str = sprintf("save_id=%s&time=%d&level=%d&wscore=%d&wuser=%s&wname=%s&details=%s",wp->query("weapon_mp/save_id"),time(),qua+1,
                        WORKER_D->weapon_rank(wp),wp->query("maker"),wp->query("name")+"("+wp->query("id")+")",st);
                //WORKER_D->update_UniqueValues("addweapon",str,wp->query("weapon_mp/save_id"));
        }
        call_out("duanzao_finish",delay,qua,me,obj,1);
	
}

void duanzao_finish(int j,object me,object obj,int win)
{
        object tools,wp;
        string str;
        int level, kuangshi, i=1, improve;

        if(!objectp(me) ||!objectp(obj)) return;
        me->start_busy(-1);
        me->interrupt_me();
        tools = me->query_temp("weapon");
        level = (int)me->query_skill("duanzao",1);
        if(level>390) level = 390 + (level-390)*11;
        kuangshi = (int)obj->query_level();

        message_vision(HIY"$N把已经锤击过无数次的兵器放入冷水之中......\n"NOR, me);
        me->delete_temp("pending/duanzao",1);
        if ( objectp(tools) && tools->query("id")=="tiechui" ) tools->use();

        switch(kuangshi) {
                case 1: i = 40;  break;
                case 2: i = 80;  break;
                case 3: i = 120; break;
                case 4: i = 170; break;
                case 5: i = 220; break;
                case 6: i = 270; break;
                case 7: i = 330; break;
                case 8: i = 390; break;
                case 9: i = 500; break;
        }
        i = 100 - (level - i)/2;
        if(i>200) i = 200;
        if(i< 10) i = 10;

        if ( me->query_temp("user_type") != "worker")
                improve = me->query_int(1)*i/100;
        else
                improve = me->query_int()*i/100;

        if( win ) {
        	WORKER_D->check_impove(me,"duanzao",improve*9,j>=4?3:2);
                //if(me->query_skill("duanzao",1)<220) me->improve_skill("duanzao", improve*9);
                if ( environment(me)->query("no_zhiye")
                 || me->query_temp("user_type") == "worker")
                 {
					int exp = me->add_exp_combat( random(improve*4/5) ,0,"铸剑",1);
					//me->add("combat_exp", random(improve*4/5)*ZY_ZHUJIAN_MUL/100  );
					//< Modified by mxzhao 2005/01/09
					//me->add("potential", random(improve/5*3)*ZY_ZHUJIAN_MUL/100  );
					me->add("potential", exp*3/4);
					//> Modified by mxzhao 2005/01/09
                }
                wp = (object)me->query_temp("worker/wp");
                if(!wp) return;
                me->delete_temp("worker/wp");
                //if( wp->query("weapon_mp/imbued")>3 && WORKER_D->query_UniqueValues("addweapon",wp->query("weapon_mp/save_id"))<0 ) {
                  //      tell_object(me , "网络错误：无法连接同步服务器，武器生成失败！\n");
                    //    destruct(wp);
                      //  return;
                //}

				//增加轮子的个数数量，by sohu
               if (wp->query("id")=="lun" )
                {
					wp->set("amount",5);
                }/**/
				
				if (wp->query("wield_maxneili")<=0) wp->set("wield_maxneili",100);
				if (wp->query("wield_neili")<=0) wp->set("wield_neili",100);
				
                if(!wp->move(me)) {
                        wp->move(environment(me));
                        tell_object(me , "但是你拿不动了！\n");
                }
				
                message_vision(HIC"$N从水缸中取出一"+wp->query("unit")+wp->name()+"。\n"NOR, me);
                if(check(me)) me->back_player(wp);
        }
        else {
        	WORKER_D->check_impove(me,"duanzao",improve*3,2);
                //if(me->query_skill("duanzao",1)<220) me->improve_skill("duanzao", improve*3);
                if ( environment(me)->query("no_zhiye")
					|| me->query_temp("user_type") == "worker") {
					int exp = me->add_exp_combat( random(improve/3) ,0,"铸剑",1);
					//me->add("combat_exp", random(improve/3) *ZY_ZHUJIAN_MUL/100 );
					//< Modified by mxzhao 2005/01/09
					//me->add("potential", random(improve/5) *ZY_ZHUJIAN_MUL/100 );
					me->add("potential", exp*3/5);
					//> Modified by mxzhao 2005/01/09
                }
                message_vision(HIC"但是$N锻造的兵器一放到冷水里，就四分五裂了！\n"NOR, me);
        }
        destruct(obj);
        if ( (int)me->query("potential", 1) > (int)me->query("max_pot", 1) )
                me->set("potential" , me->query("max_pot", 1) );
        me->set("worker/duanzao",time()+10+random(20));

        str = WORKER_D->worker_title(me,"duanzao");
        // 工匠title
        me->set_temp("title", str);
}

int do_xiu(string arg)
{
        object me = this_player() ,obj,obj2,weapon;
        int delay,level,flag;
        string str;

        if (me->is_busy()) return notify_fail("你正忙着呢！\n");
        if (me->is_fight()) return notify_fail("你正忙着呢！\n");
        if (!arg) return notify_fail("你要修什么？\n");
        if ( !objectp(obj = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");        
        if ( !objectp(weapon=me->query_temp("weapon")) || weapon->query("id")!="tiechui" )
                return notify_fail("你必须装备铁锤才能来维修兵器。\n");
	//if(!obj->query("broken"))
		//return notify_fail("这个武器尚未完全损害，你可以尝试(repair)修理它。\n");
	if(!mapp(obj->query_temp("apply/weapon_mp_old")) && (!mapp(obj->query("weapon_prop")) || !(int)obj->query("imbued") ) )
		return notify_fail("在这里只能维修由玩家制造的兵器。\n");
        if (!obj->query("broken") &&  obj->query("weapon_mp/dur") >= obj->query("weapon_mp/max_dur") )
                return notify_fail("这件兵器完好无损，无需修理。\n");
	//if ( !mapp(obj->query("weapon_prop")) || !(int)obj->query("imbued") )
                //return notify_fail("在这里只能维修由玩家制造的兵器。\n");
        //if ( obj->query("weapon_mp/dur") <= 0  )
                //return notify_fail("这件兵器已经彻底损坏了，无法修理。\n");
		
	flag = strsrch(obj->query("save_id"),"weilan tiejiang")==0;
	
        switch( (string)obj->query("material") ){
               // case "hantie":   str =	HIC"万年寒冰铁"NOR; break;
				case "xuantie":   str = WHT"玄铁"NOR; break;
                case "shentie":   str = RED"万年神铁"NOR; break;
                case "jintie":    str = HIY"金铁"NOR; break;
                case "ruanying":  str = HIW"软银"NOR; break;
                case "liuhuashi": str = RED"流花石"NOR; break;
                case "lushi":     str = HIG"绿石"NOR; break;
                case "ruantie":   str = YEL"软铁"NOR; break;
                case "shengtie":  str = YEL"生铁"NOR; break;
                case "qingtong":  str = GRN"青铜"NOR; break;
                default: str =  "精钢"; break;
        }
        if (!flag && !objectp(obj2 = present((string)obj->query("material"), me)) )
                return notify_fail("你需要一块"+str+"，才能维修这件兵器。\n");

        level = (int)me->query_skill("duanzao",1);
        if(!flag) switch( (int)obj2->query_level() ) {
                case 1: if(level<10)  return notify_fail("你的锻造技能不够！\n"); break;
                case 2: if(level<40)  return notify_fail("你的锻造技能不够！\n"); break;
                case 3: if(level<80)  return notify_fail("你的锻造技能不够！\n"); break;
                case 4: if(level<120) return notify_fail("你的锻造技能不够！\n"); break;
                case 5: if(level<170) return notify_fail("你的锻造技能不够！\n"); break;
                case 6: if(level<220) return notify_fail("你的锻造技能不够！\n"); break;
                case 7: if(level<270) return notify_fail("你的锻造技能不够！\n"); break;
                case 8: if(level<330) return notify_fail("你的锻造技能不够！\n"); break;
                case 9: if(level<390) return notify_fail("你的锻造技能不够！\n"); break;
        }
        if(flag)
        	switch(MONEY_D->player_pay(me,obj->query("value")/2))
        	{
        		case 1:break;
        		default:return notify_fail("你带的零钱不够了！你需要"+MONEY_D->money_str(obj->query("value")/2)+"修理费用。\n");
        	}
        message_vision(HIY"$N开始仔细的维修"+obj->query("name")+HIY"，不时用铁锤敲敲打打......\n\n"NOR, me);
        delay = 15 + random(30);
        if(wizardp(me) && (int)me->query("env/test")) delay = 3;
        me->start_busy(delay);
        if(!flag && obj2) destruct(obj2);
        call_out("xiu_finish",delay*2-1,me,obj);
        return 1;
}

int decvar(object ob,string type,int times,int decmin,int min)
{
        int i,j;

        if( times <= 0 ) return 0;
        i = (int)ob->query(type) * 100;
        if( i == 0 ) return 0;
        decmin *= 100;
        min *= 100;

        j = i / times;
        if( j < decmin ) j = decmin;
        i = i - j;
        if( i < min ) i = min;

        ob->set(type,i/100);
        return i/100;
}

void xiu_finish(object me,object obj)
{
        object tools;
        int i;

        if(!objectp(me) || !userp(me) || !objectp(obj) ) return;
        
        
	obj->delete("broken");
	obj->delete("treasure");
			        
        if(obj->query_temp("apply/weapon_mp_old")) obj->set("weapon_mp",obj->query_temp("apply/weapon_mp_old") );
	if(obj->query_temp("apply/name_old")) obj->set("name",obj->query_temp("apply/name_old"));
	if(obj->query_temp("apply/weapon_prop_old")) obj->set("weapon_prop",obj->query_temp("apply/weapon_prop_old"));
	if(obj->query_temp("apply/long_old")) obj->set("long",obj->query_temp("apply/long_old"));
	
	obj->delete_temp("apply");
	
        message_vision(HIY"$N仔细的维修"+obj->query("name")+HIY+"，总算大致恢复了它的原貌。\n"NOR, me);
        WORKER_D->check_impove(me,"duanzao",me->query_int()/2,2);
        //me->improve_skill("duanzao", me->query_int()/2);

        i = decvar(obj,"weapon_mp/max_dur",9,10,100);
        obj->set("dur",i);
        obj->set("weapon_mp/dur",i);
        obj->set("weapon_mp/max_dur",i);

        decvar(obj,"weapon_prop/damage",5+random(7),10,10);
        decvar(obj,"weapon_prop/qi",5+random(7),50,10);
        decvar(obj,"weapon_prop/jing",5+random(7),50,10);
        decvar(obj,"weapon_prop/jingli",5+random(7),50,10);
        decvar(obj,"weapon_prop/neili",5+random(7),50,10);
        decvar(obj,"weapon_prop/attack",5+random(8),3,1);
        decvar(obj,"weapon_prop/dodge",5+random(8),3,1);
        decvar(obj,"weapon_prop/parry",5+random(8),3,1);

        i = decvar(obj,"weapon_mp/rigidity",5,1,1);
        obj->set("rigidity",i);
        i = decvar(obj,"weapon_mp/sharpness",5,1,1);
        obj->set("sharpness",i);
        i = decvar(obj,"weapon_mp/value",6,10,1);
        obj->set("value",i);
        
        obj->set("weapon_mp/weapon_prop",copy(obj->query("weapon_prop")));

        obj->save_weapon(me);

        tools = me->query_temp("weapon");
        if ( objectp(tools) && tools->query("id")=="tiechui" ) tools->use();
}

nosave string *banned_name = ({
// Mud 保留名字
"杀手","闪电","雪人","我们","天神","总管","龙神","仙人","巫师","玩家","书剑","杀人犯","祈雨","迎风",
// Mud 地名，门派名
"少林","丐帮","明教","密宗","慕容","古墓","全真","铁掌","大理","白驼","桃花","星宿",
"天龙寺","大轮寺","五毒教","正义","邪恶","五岳剑派","日月神教","官府","武林",
"少林寺","武当派","铁掌帮","普通百姓","峨嵋派","姑苏慕容","古墓派","华山派","嵩山派",
"明教","神龙教","星宿派","血刀门",
// 重要人物名字
"金庸","邓小平","江泽民","毛泽东","朱榕基","皇帝","总理", "主席",
// 小说人物
"张三丰","张无忌","郭靖","杨过","令狐冲","胡斐","苗人凤","韦小宝","袁承志","胡一刀",
"陈家洛","段誉","萧锋","乔锋","虚竹","东方不败","欧阳锋","洪七公","黄药师","段皇爷",
"一灯大师","王重阳","周伯通","黄蓉","风清扬","独孤求败",
// 脏话
"统一","法轮","法轮研究","法轮大","吃人","他妈的","去你的","操你妈","干你娘","废物",
"混蛋","坏蛋","杀人","抢劫","强奸","妓女","台独","领导","中央","屁眼","屁股","裸体",
"放屁","鸡巴","阴道","婊子","你丫","日你","赤佬","瘪三","傻逼","蠢蛋","操他","我操",
"太监","宦官","阉割","阉人","鸡", "奸淫", "淫荡", "轮奸", "奸", "三级", "政治",
});

nosave string *banned_name2 = ({
// 兵器名
"打狗棒",
"哭丧棒",
"狼牙棒",
"玉竹棒",

"青焰刀",
"屠龙刀",
"血刀",
"鸯刀","鸳刀","鸳鸯刀",
"紫金刀",

"黄金棍",

"白虹剑","碧玉剑","碧水剑","碧血剑",
"东灵铁剑",
"观日剑",
"冷月宝刀","绿波香露刀",
"金蛇剑","君子剑",
"青冥剑",
"辟邪剑",
"书剑","淑女剑",
"无名宝剑",
"玄铁剑",
"倚天剑","游龙剑",
"真武剑","周公剑",

"碧玉箫",
"洞箫",
"紫玉箫",

"九环锡杖",
});
