// dong1.c
// sohu
#include <ansi.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h"
int check_fight(object me,object laozu,object shui);

void create()
{
        set("short",YEL"野山洞"NOR);
        set("long",@LONG
这是一个小小的山洞，仅供二人藏身之地。由於此地比较隐秘
乃是大雪山深处的天然洞穴，外人很难寻到这里来。
LONG );
        set("exits",([
                "out" : "/d/xueshan/xuegu2",
        ]));
		set("task",1);
        set("objects", ([
               "/d/xuedao/obj/dachang" :1, 
        ]));
        setup();
  		replace_program(ROOM);
}

int init()
{
	object shui;
	object me=this_player();
	
	if (me->query_temp(QUESTDIR3+"shuitellstory")&&this_object()->query("task")>0)
	{
		message_vision(HIC"$N来到这个山洞，见水笙还没到达，就随意向四周打量!\n"NOR,me);
		message_vision(HIM"忽听洞外有人喊道，“师妹！你原来躲在这儿，师兄我找的你好苦啊！”\n"NOR,me);

		call_out("wang_come",2+random(3),me);
		//调用检查程序
		//call_out("check_fight",1,me);

		me->set_temp(QUESTDIR3+"fightwang",1);
		me->delete_temp(QUESTDIR3+"shuitellstory");
		this_object()->add("task",-1);

	}
		        //调用保护水笙函数
	//add_action("do_baohu", "baohu");
	add_action("do_qiang", "qiang");
	add_action("do_canwu", "canwu");

}

int wang_come(object me)
{
		object wang;
		if (!me) return 0;
	
		if (me->query("gender")=="男性")
			message_vision(HIW"汪啸风嗅了嗅鼻子，一见$N站旁边，顿时大怒，喝道：“我师妹在这待过，原来是你这小白脸在此勾引我师妹！”\n"NOR,me);
		if (me->query("gender")=="女性")
			message_vision(HIW"汪啸风一间$N站在水笙旁边，顿时大怒，喝道：“原来是你这小骚货在此诱惑教唆我师妹跟我作对！”\n"NOR,me);

		if (!objectp(wang=present("wang xiaofeng",this_object())))
		{
			wang=new("d/xuedao/npc/wangxiaofeng");
			wang->move("d/xuedao/dong");
		}
		wang->kill_ob(me);
		me->kill_ob(wang);
		me->set_temp(QUESTDIR3+"killwang",1);

		message_vision(HIR"汪啸风向洞外喝道：“师傅快来，师妹在这儿，这淫贼正在欺负我师妹！”\n"NOR,me);
		if (living(me))
			call_out("lhls_come",10+random(10),me);
		return 1;
}
//落花流水来了

int lhls_come(object me)
{
		object lu,hua,liu,shui;
		if (!me) return 0;

		tell_object(me,HIY"落~~~~~~~~~~~~~~~~~~~~~~~！\n"NOR);
		tell_object(me,HIG"~~~~~~~~花~~~~~~~~~~~~~~~！\n"NOR);
		tell_object(me,HIW"~~~~~~~~~~~~~~~~流~~~~~~~！\n"NOR);
		tell_object(me,HIM"~~~~~~~~~~~~~~~~~~~~~~~水！\n"NOR);

		message_vision(HIR"落花流水，江南四大侠，一见$N站在水笙旁边，顿时大怒，喝道：“原来是你在弄计谋，该死！”\n"NOR,me);

		if (!objectp(lu=present("lu tianshu",this_object())))
		{
			lu=new("d/xuedao/npc/lutianshu");
			lu->do_copy(me);
			lu->move("d/xuedao/dong");

		}
		if (!objectp(hua=present("hua tiegan",this_object())))
		{
			hua=new("d/xuedao/npc/huatiegan");
			hua->do_copy(me);
			hua->move("d/xuedao/dong");

		}
		if (!objectp(liu=present("liu chengfeng",this_object())))
		{
			liu=new("d/xuedao/npc/liuchengfeng");
			liu->do_copy(me);
			liu->move("d/xuedao/dong");

		}
		if (!objectp(shui=present("shui dai",this_object())))
		{
			shui=new("d/xuedao/npc/shuidai");
			shui->do_copy(me);
			shui->move("d/xuedao/dong");

		}

		lu->kill_ob(me);			message_vision(HIG"陆天抒喝道：“交出秘籍，饶你不死！”\n"NOR,me);

		me->kill_ob(lu);
		hua->kill_ob(me);			message_vision(HIG"花铁干喝道：“交出秘籍，饶你不死！”\n"NOR,me);

		me->kill_ob(hua);
		liu->kill_ob(me);			message_vision(HIG"刘承风喝道：“交出秘籍，饶你不死！”\n"NOR,me);

		me->kill_ob(liu);
		shui->kill_ob(me);			message_vision(HIG"水岱喝道：“交出秘籍，饶你不死！”\n"NOR,me);

		me->kill_ob(shui);
		
		me->set_temp(QUESTDIR3+"fightlhls",1);

		if (living(me))
			call_out("shuisheng_come",10+random(10),me);
		return 1;
}
//水笙来了

void shuisheng_come(object me)
{
        object shui;
		if (!me) return;


		if (!objectp(shui=present("shui sheng",environment(me))))
		{
		    shui=new("d/xuedao/npc/shuisheng");
			shui->move("d/xuedao/dong");
			
		}
		me->set_temp(QUESTDIR3+"shuicomedong",1);

		message_vision(HIC"\n水笙慌慌张张地跑了进来，面色苍白，气喘吁吁。\n一边跑，一边不住向后看，似乎后面有人正在追赶似得。\n"NOR, me);
		if (living(me))
			call_out("laozu_come",3,me,shui);
		return;
}
//老祖

int laozu_come(object me,object shui)
{
		object laozu;
		if (!me) return 0;

		if (!objectp(laozu=present("xuedao laozu",environment(me))))
        {
			  laozu=new("/d/xuedao/npc/laozu.c");
		      laozu->move(environment(me));
		      message_vision(HIY"\n屋外传来一阵淫笑，一个色眯眯的老和尚看似甚是悠闲，随后跨进门来。\n"NOR,me);
			
        }
		message_vision(HIY"\n血刀老祖色迷迷地对水笙笑道，本佛爷这次捉了个极品小妞。说完淫笑连连地就朝水笙抓去！\n"NOR,me);

		laozu->hit_ob(shui);
		shui->kill_ob(laozu);
		me->set_temp(QUESTDIR3+"laozukillshui",1);
		//调用检测函数
	//	call_out("check_fight",10,me,shui);
		//狄云来了
		if (living(me)&&objectp(laozu))
			call_out("diyun_come",3+random(2),me,laozu);
		return;
}
//开始大战狄云vs血刀老祖
int diyun_come(object me,object laozu)
{
	object diyun;
	if (!me) return 0;
	message_vision(HIR"这时，洞外传来大喝一声道，“住手！”\n"NOR,me);
	message_vision(HIG"一个长得宛如农夫样的男子进入洞中和血刀老祖斗了起来，正是狄云来了！\n"NOR,me);

	if (!objectp(diyun=present("di yun",environment(me))))
	{
		diyun=new("d/xueshan/npc/diyun");
		diyun->move(environment(me));
	}
	//laozu->kill_ob();
	if (me->query("combat_exp")<17000000)
		laozu->set("combat_exp",17000000);
	else laozu->set("combat_exp",me->query("combat_exp")*5/4);
	
	laozu->set("jiali",1);
	diyun->set("jiali",1);
	laozu->add_temp("apply/parry",200);
	laozu->add_temp("apply/armor",100);
	laozu->add_temp("apply/defense",200);

	laozu->hit_ob(diyun);
	diyun->hit_ob(laozu);
	
	message_vision(CYN"血刀老祖和狄云二话不说，开始打斗起来！\n"NOR,me);
	message_vision(YEL"洞中刀光剑影，剑气纵横，你看水笙待在一旁，似乎甚是紧张。\n悄声对水笙说道，“水姑娘，有我在不用害怕，我来保护你”！\n"NOR,me);
	add_action("do_baohu", "baohu");

	return 1;
}

//保护水笙
int do_baohu(string arg)
{
	object me,shui,laozu,diyun;
	me=this_player();
	
	shui=present("shui sheng",environment(me));
	laozu=present("xuedao laozu",environment(me));
	diyun=present("di yun",environment(me));
	if (!me->query_temp(QUESTDIR3+"laozukillshui")) return notify_fail("你无缘无故张开双臂要伸懒腰么？\n");
	if (time()-me->query(QUESTDIR+"time")<86400)
	{
		return notify_fail("你已经保护过一次，明天再来！\n");
	}


	if (!arg||arg!="水笙") return notify_fail("你要保护谁？\n");

	if (!shui) return notify_fail("你动作太慢，水笙已经不在此地，你发花痴了吧？\n");
	if (!laozu) return notify_fail("老祖已经被杀了，无需保护水笙？\n");
	if (!diyun) return notify_fail("狄云不小心被杀了，水笙陷入极度悲伤之中，失败？\n");
	
	if (me->query_temp(QUESTDIR3+"baohu"))
	{
		return notify_fail("你正在实施保护过程中？\n");
	}

	message_vision(HIG"$N眼见水笙危及，对$n说道，“水姑娘不要着急，我来保护你！”\n"NOR,me,shui);
	message_vision(HIY"$n大喝一声道，“$N又开始装大蒜瓣了，老子干的就是装逼的英雄！”\n"NOR,me,laozu);
	
	message_vision(HIM"$n血刀经发动，仿佛变了个人似得，周身腾起一片若隐若现的血雾！\n"NOR,me,laozu);

	if (me->query("combat_exp")<17000000)
		laozu->set("combat_exp",17000000);
	else laozu->set("combat_exp",me->query("combat_exp")*5/4);
	//laozu->set("jiali",250);
	if (me)
		laozu->kill_ob(me);
	if (diyun)
		laozu->kill_ob(diyun);
	
	laozu->kill_ob(shui);
	me->set_temp(QUESTDIR3+"baohu",1);
//是汉子挺住10秒
//	if (living(me)&&objectp(laozu)&&objectp(shui))
		call_out("check_fight",10,me,laozu,shui);
	return 1;
}
//检查条件
int do_fail(object me)
{
	
	me->set(QUESTDIR+"time",time());
	me->add(QUESTDIR3+"fail",1);
	me->set(QUESTDIR+"combat",me->query("combat_exp"));
	me->delete_temp(QUESTDIR3);

	message_vision(HIC"\n\n\n$N救护水笙失败,需再接再厉!\n\n\n"NOR,me);

}
int check_fight(object me,object laozu,object shui)
{
	object weapon;
	if (!me) return 1;
	
	if (!shui) 
	{
		tell_object(me,HIR"你因为救护水笙不利，导致水笙为老祖所劫掠，任务失败！\n"NOR);

		do_fail(me);
		return 1;
	}
	if (environment(me)!=this_object())
	{
		tell_object(me,HIR"你因为擅自离开山洞，救护水笙不利，导致任务失败！\n"NOR);
		do_fail(me);
		return 1;
	}
	//laozu=present("xuedao laozu",environment(me));
	
	if (!objectp(laozu))
	{
		tell_object(me,HIR"老祖不在此地，后续情节无法继续，导致任务失败！\n"NOR);
		do_fail(me);
		return 1;
	}

	weapon=laozu->query_temp("weapon");
	message_vision(HIW"$N叫道：“别再杀人了！”说完扑将上去，手中树枝击在$n腕上。\n"NOR, shui, laozu);
	if (weapon)
	{
		message_vision(HIC"若在平时，$n焉能给$N击中？但这时衰颓之余，功力不到原来的半成，手指一松，"+weapon->query("name")+HIC"脱手落地。\n"NOR,shui, laozu);
		weapon->move(environment(me));
	}
	message_vision(HIC"\n\n方才血刀老祖手持血刀的凶恶和凶狠让你记忆尤新，$N忽然意识道，必须将地上的这把刀抢过来。\n\n"NOR,me);
	message_vision(HIY"\n否则一旦再让血刀老祖抢到那把刀，在场所有的人恐怕都难以活命！\n\n\n"NOR,me);
	//清除前面标记

	me->delete_temp(QUESTDIR3);

	//设定保护水笙标记
	me->set_temp(QUESTDIR3+"baohushuisheng",1);

	return 1;

}
//抢兵器


int do_qiang(string arg)
{
	object me = this_player(), ob;
	
	if (!me->query_temp(QUESTDIR3+"baohushuisheng")) return notify_fail("你连保护水笙这件事都做不了，还呈什么英雄？\n");

	if (arg != "刀" && arg !="dao") return notify_fail("你要抢夺什么？\n");
	
	if (me->is_busy())
		return notify_fail("你已经手忙脚乱中，你还抢啥抢？\n");
	if (me->query_temp(QUESTDIR3+"qiangdao"))
		return notify_fail("你已经在抢了，还抢啥抢？\n");
	
	
	
	me->set_temp(QUESTDIR3+"qiangdao",1);

	ob = present("xuedao laozu", this_object());
	
	if (!ob) 
	{
		return notify_fail("血刀老祖都死了，你还抢啥抢？\n");
	}
	message_vision(HIW"$N和$n同时俯身去抢兵刃。$N手掌在下，先按到了刀柄。\n"NOR, me, ob);
	message_vision(HIC"$n提起双手，便往$N颈中扼去。$N一阵窒息，放开了血刀，伸手撑持。\n"NOR, me, ob);
	message_vision(HIC"$n知道自己力气无多，这一下若不将$N扼死，自己便命丧$N手。\n"NOR, me, ob);
	message_vision(HIC"$N头颈被$n扼住，呼吸越来越艰难，胸口如欲迸裂。\n\n"NOR, me, ob);
	me->start_busy(100);
	call_out("story3", 3+random(3), me, ob);
	return 1;
}


void story3(object me, object ob)
{
	
	if (me->query_skill("shenzhao-jing", 1) < 550) 
	{
		tell_object(me,HIC"终因神照经等级不足550级,尚未融会贯通，无法体味那种意境！\n"NOR);
		call_out("finish", 1, me);
		return;
	}
	tell_object(me, RED"你肺中积聚着的一股浊气数度上冲，要从口鼻中呼了出来，但喉头的要道被阻，这股气冲到喉头，又回了下去。\n"NOR);
	tell_object(me, RED"一股浊气在你体内左冲右突，往来奔赴，始终找不到出路。\n"NOR);
	tell_object(me, HIM"你只感全身难受困苦已达极点，心中只叫：“我快要死了，我快要死了！”\n\n"NOR);
	tell_object(me, HBYEL+HIW"在此生死忧关的关键时刻，你忽然有所明悟，进入一种玄妙的境界，有些灵魂出窍的感觉！\n\n"NOR);
	tell_object(me, HIG"你生死一线，苦苦挣扎，但却四肢无力，心中狂喊：“我快要死了！”\n\n"NOR);
	
	call_out("story4", 3+random(3), me, ob);
}

void story4(object me, object ob)
{
		object shui,diyun;

		shui=present("shui sheng",environment(me));
		if (!me) return;
	
		if (!shui) 
		{
			
			return notify_fail("世间恩怨聚汇，前因后果均和你无关，你挣扎半天，也没有一个人救你\n而本应该救你之人却因你保护不力而香陨，是耶非耶！？\n");
		}
		if (!ob) 
		{
			
			return notify_fail("血刀老祖都被你杀了，还怎么搞下去？？\n");
		}

		tell_object(me, HIM"此时水笙眼见情况危急，奋力将那柄刀抢到手中！”\n\n"NOR);
		
		tell_object(me, HIY"血刀老祖一时疏忽，微一愣神间！对水笙怒目而视，喝道“臭妮子，把刀给我！”\n"NOR);

		message_vision(HIC"$N体内的劲力愈来愈强，心中却仍是十分害怕，只求挣扎脱身，双手乱抓乱舞，始终碰\n"
							"不到$n身上，左脚向后乱撑几下，突然一脚踹在$n的小腹丹田之上。\n\n"NOR, me, ob);
		message_vision(HIR"血刀老祖一声惨嚎，顿时昏迷倒地。\n\n"NOR, me, ob);
		ob->unconcious();

		tell_object(me, RED"水笙为血刀老祖方才一吓，心中一慌，手中刀拿捏不住，顺势掉了下来！\n"
				+"正好切在昏迷在地血刀老祖的脖颈上，那刀锋利异常，顿时将血刀老祖身首异处！”\n"NOR);
		ob->die();
		
		me->start_busy(1);

		message_vision(HIY"$N有气无力地对水笙说道：姑娘你走吧，否则血刀老祖醒来一定不会放过你的。\n"NOR, me);

		message_vision(HIY"$n双目茫然，盲目地点点头，说道，“都死了，全都死了！”\n"NOR, me, shui);
		message_vision(HIG"$n说完哭着向外面跑去。\n\n"NOR, me, shui);
		message_vision(HIC"狄云也随后追了出去。\n\n"NOR, me, shui);
		if (shui)
			destruct(shui);
		if (diyun)
			destruct(diyun);
		message_vision(HBYEL+HIW"恭喜你，终于完成《连城诀》之《雪山奇遇篇》章节故事内容！\n"NOR,me);
		message_vision(HBYEL+HIW"剩下的关于连城诀武功“神照经神功”的参悟就依靠你以后在此不断参悟了！\n"NOR,me);
		message_vision(HBYEL+HIW"而连城诀空手武功之“无影神拳”部分将陆续开放！\n"NOR,me);
		me->set(QUESTDIR3+"over",1);
		return;
	
}
/*
void finish(object me, object ob)
{
	object obj = present("shui sheng", this_object());
	if (!obj) return;
	message_vision(HIY"$n冷哼一声，小崽子自不量力，看在你给老子找女人的分上饶你不死。\n"NOR, me, ob);
	message_vision(HIY"可是这个小妞咱可不能放过，否则等她力气恢复了，肯定会杀了我们两个。\n"NOR, me, ob);
	message_vision(HIY"$n挥刀砍向水笙，水笙躲避不及，鲜血从喉咙口直流出来。\n"NOR, me, ob);
	obj->die();
	me->start_busy(1);
	me->unconcious();
}*/
/*
*/

int do_canwu(string arg)
{
	int i,j,x;
	object*obj;
	object me=this_player();

	obj = users();
	x = sizeof(obj);
	
	while(x--) {
		  if ( obj[x]->query_temp("quest/szj/shenzhao/canwu")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N试图参悟神照经神功，却发现"+obj[x]->query("name") +HIY"已经在哪儿打坐参悟，只得先行在洞外等候！\n"NOR,me);	
				  me->move("d/xueshan/xuegu2");
				  return 1;
			}
			
	}

	if (!arg||arg!="神照经神功")
	{
		return notify_fail("你要参悟什么神功？\n");
	}

	if (!me->query(QUESTDIR3+"over") )
	{
		return notify_fail("你尚未完成《连城诀》之《奇遇篇》章节故事内容！\n");
	}
	if (me->query_skill("shenzhao-jing",1)<550)
	{
		return notify_fail("神照经不足550，无法融会贯通！\n");
	}
	
	if (me->query("quest/szj/pass")==3 || me->query("quest/shenzhao/laozu"))
	{
		return notify_fail("你已经解开此谜题！\n");
	}

	if ((time()-me->query(QUESTDIR+"time"))<86400)
	{
		return notify_fail("你已经很累了，隔日再来！\n");
	}
	if( (string)me->query("gender") == "无性" )
		return notify_fail("施主身体残缺，阴阳难以调和，无法参悟神照经高级功法。\n");
	
	if (me->query_temp("quest/szj/shenzhao/canwu"))
	{
		return notify_fail("你正在参悟神照经神功之中!\n");

	}
	if (me->is_busy())
		return notify_fail("你已经手忙脚乱中，无法参悟？\n");

	if (this_object()->query("shenzhao/canwu"))
	{
		return notify_fail("嘘！有人正在参悟神照经神功之中，请勿打扰!\n");

	}

	message_vision(HIW"$N平心静气，舒缓而坐，面对墙壁，闭目冥想，回想当初和老祖搏斗间发生的一幕幕情景！\n"NOR,me);
	message_vision(HIW"$N看自己能否再次进入那种玄妙的境界中体悟！\n"NOR,me);

	me->set_temp("quest/szj/shenzhao/canwu",1);
	me->start_busy(99);
	
	this_object()->set("canwu/shenzhao",1);

	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}
//辅助判断
// 先天悟性42，福源，随机数

int thinking(object me)
{
	int i,j,k; 
	if(!me) return 0;
	
	k=random(me->query("kar"));
	j=20;
	i=me->query("int");

	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	
	if(me->query_temp("shenzhao_cw")<(15+random(10)))
    {  
	  me->add_temp("shenzhao_cw",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你忽觉眼前出现一片白云如棉，缓缓将你包括起来.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n你仔细琢磨真气运转的技巧，似乎有些心得。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你一时心气浮躁，结果真气运转都没控制好，有走火入魔的危险！\n"NOR);
			 me->add_temp("shenzhao_cw",-2);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，万事不萦于怀，想了想，似乎有所心得.\n"NOR);
			me->add_temp("shenzhao_cw",1);

			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎即将崩溃.\n"NOR);
			me->add_temp("shenzhao_cw",-1);

			break;
		case 5:
			tell_object(me,MAG"\n你浑身一轻，真气澎湃，灵活的很，似乎隐隐约约看到一丝曙光！\n"NOR);
			me->add_temp("shenzhao_cw",3);

			break;

		default:tell_object(me,YEL"\n你心浮气躁，难以入冥.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"盘膝而坐，面向石壁，无欲无求。\n"NOR, ({}));

	  call_out("thinking",3+random(3), me);

   } 
   else if (k>27
	  && random(j)<2
	  && random(i)>41
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 tell_object(me, HIW"突然之间，你只觉胸腹间剧烈刺痛，体内这股气越胀越大，越来越热，犹如满镬蒸气\n"
						"没有出口，直要裂腹而爆，蓦地里前阴后阴之间的“会阴穴”上似乎被热气穿破了一个小\n"
						"孔，登时觉得有丝丝热气从“会阴穴”通到脊椎末端的“长强穴”去。人身“会阴”“长\n"
						"强”两穴相距不过数寸，但“会阴”属于任脉，“长强”却是督脉，两脉的内息决不相通。\n"
						"你体内的内息加上无法宣泄的一股巨大浊气，交迸撞激，竟在危急中自行强冲猛攻，替你\n"
						"打通了任脉和督脉的大难关。这内息一通入“长强穴”，登时自腰俞、阳关、命门、悬枢\n"
						"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"
						"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
	
		tell_object(me, HIY"这股内息冲到百会穴中，只觉颜面上一阵清凉，一股凉气从额头、鼻梁、口唇下来，通到\n"
						"了唇下的“承浆穴”。这承浆穴已属任脉，这一来自督返任。任脉诸穴都在人体正面，这\n"
						"股清凉的内息一路下行，自廉泉、天突而至璇玑、华盖、紫宫、玉堂、膻中、中庭、鸠尾、\n"
						"巨阙、经上、中、下三脘，而至水分、神厥、气海、石门、关元、中极、曲骨诸穴，又回\n"
						"到了“会阴穴”。如此一个周天行将下来，郁闷之意全消，说不出的畅快受用。内息第一\n"
						"次通行时甚是艰难，任督两脉既通，道路熟了，第二次、第三次时自然而然的飞快运转，\n"
						"顷刻之间，连走了一十八次。\n\n"NOR);
		message("channel:rumor", MAG"【谣言】某人："+me->query("name")+"机缘巧合，运使神照经打通了任督二脉，达到了神照经心法的最高境界！\n"NOR, users());
		message("channel:rumor", MAG"【谣言】某人：恭喜"+me->query("name")+"解开神照经第三节绝世武功，从此天地高阔！\n"NOR, users());

         message_vision(HIW"\n$N心中大喜，「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断研磨领悟，终于领悟了神照经第三段的武功精要，神照经至此大成！”\n"NOR,me);
		 
         log_file("quest/shenzhaojing", sprintf("%s(%s) 神照经绝世武技解密成功！失败第%d次后参悟，机缘巧合下，当前随机幸运值：%d,当前随机值：%d,当前先天悟性值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query(QUESTDIR3+"fail"),
		 k,
		 j,
		 i,
         me->query("combat_exp"),
		 ));

		 me->set(QUESTDIR+"time",time());
		 me->delete_temp("shenzhao_cw");
		 me->delete_temp("quest/szj");
		 this_object()->delete("canwu");

		 me->set("quest/szj/pass",3);
		 me->set("quest/shenzhao/laozu",1);//兼容问题
		 
		 me->set("title",HBMAG+HIW"连城诀*神境坐照"NOR);
		 me->set("mytitle/quest/szj3",HBMAG+HIW"连城诀*神境坐照"NOR);
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这神照经神功真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HBYEL+HIW"\n非常遗憾，参悟神照经神功第三段解密失败！\n"NOR,me); 
         log_file("quest/shenzhaojing", sprintf("%s(%s) 失败神照经神功参悟！第%d次失败，随机幸运值：%d,当前随机值：%d,当前先天悟性值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query(QUESTDIR3+"fail"),
		 k,
		 j,
		 i,
         me->query("combat_exp"),));        
		 
		 me->add(QUESTDIR3+"fail",1);
		 me->set(QUESTDIR+"time",time());
		 me->start_busy(2);
		 me->delete_temp("shenzhao_cw");
		 me->delete_temp("quest/szj");
		 this_object()->delete("canwu");
		 me->start_busy(1);
		 return 1;
   }



}