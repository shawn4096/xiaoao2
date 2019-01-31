// ren.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_bijian();
int ask_ronggong();
int ask_dongfang();
int ask_xxdf();
int ask_ruozhuo();
int ask_qianbian();
void create()
{
	set_name("任我行", ({ "ren woxing", "ren","woxing" }));
	set("nickname",HIR"魔教教主"NOR);
	set("long", "只见他一张长长的脸孔，脸色雪白，更无半分血色，眉目清秀，
身材甚高，一头黑发，穿的是一袭青衫。\n");
	set("gender", "男性");
	set("age", 55);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("no_get", 1);
	set("str", 30);
	set("per", 27);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 40000);
	set("max_jing", 10000);
	set("eff_jingli",10000);
	set("neili", 80000);
	set("max_neili", 40000);
 	set("jiali", 200);
	set("combat_exp",12000000);
	set("score", 500000);
    set("xixing",2);
	//set("quest/");

	set_skill("literate", 200);         // 读书识字
	set_skill("force",500);            // 基本内功
	set_skill("strike",500);           // 基本指法
	set_skill("dodge",500);            // 基本躲闪
	set_skill("parry",500);            // 基本招架
	//set_skill("dagger",400);           // 基本刺法
	set_skill("sword",500);            // 基本剑法
	set_skill("blade",500);
	set_skill("club",500);
	set_skill("poison",180);
	set_skill("throwing",500);
	set_skill("huanmo-wubu",500);  // 缥缈身法
	set_skill("tianmo-gun",500);  // 幻魔胧天舞
	set_skill("qixian-wuxingjian",500);// 七弦无形剑
	set_skill("xixing-dafa",500);      // 吸星心法
	//set_skill("wudang-quan",400);        // 太祖长拳
	set_skill("damo-jian",500);        // 达摩剑法
	set_skill("taiji-jian",500);       // 太极剑法
	set_skill("huifeng-jian",500);     // 回风拂柳剑
	set_skill("taishan-jianfa",500);    // 泰山剑法
	set_skill("hengshan-jianfa",500);    // 恒山剑法
	set_skill("mantian-huayu",500);   // 
	set_skill("huashan-jianfa",500);    // 华山剑法
	set_skill("songshan-jian",500);   // 嵩山剑法
	set_skill("tianmo-jian",500);
	set_skill("tianmo-zhang",500);
	//set_skill("tianmo-shou",400);
	set_skill("tianmo-dao",500);
	set_skill("tianmo-gun",500);
	set_skill("tianmo-jue",200);

	map_skill("force", "xixing-dafa");
	map_skill("blade", "tianmo-dao");
	map_skill("club", "tianmo-gun");
	map_skill("sword", "qixian-wuxingjian");
	map_skill("strike", "tianmo-zhang");
	map_skill("dodge", "huanmo-wubu");
	map_skill("parry", "qixian-wuxingjian");
	prepare_skill("strike", "tianmo-zhang");
	set("quest/xixing/pass",2);
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
                (: perform_action, "sword.qianbian" :),
                (: perform_action, "sword.pomo" :),
                (: exert_function, "xixing" :),
	}));

    set("inquiry", ([
                "比剑" :  (: ask_bijian :),
                "剑法" :  (: ask_bijian :),
                "黑木令" : "要拿黑木令？老夫想先看看你的剑法！\n",
	        	"日月神教" : "你想加入我日月神教，就得找四大堂长老。",
		        "吸星大法融功"     :  (: ask_ronggong :),
                "东方不败"     : (: ask_dongfang :),
			    "吸星大法拓本"     : (: ask_xxdf :),
			    "千变万化绝技"     : (: ask_qianbian :),
			    "天魔掌绝技"     : (: ask_ruozhuo :),
	]) );

	create_family("日月神教", 5, "教主");
 	setup();
	carry_object("/clone/armor/changpao")->wear();
	carry_object("/clone/weapon/sword")->wield();
}

int ask_bijian()
{
	object weapon, me = this_player(), ob = this_object();

        if (!objectp(weapon = ob->query_temp("weapon")))
	{
		weapon = new("/clone/weapon/sword");
		weapon -> move(ob);
		command("wield sword");
	}
	if(me->query("combat_exp")<5000000)
	{
		message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n$n冷笑道：“你这点经验敢跟我比剑？过了5m后再说！”\n", me, ob );
		message_vision("$n趁$N发愣之际，一脚将$N踢出了监狱！”\n", me, ob );
		me->move("d/hz/baidi");
		return 1;
	}
	if(!me->query_temp("quest/xxdf/start"))
	{
		message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n$n冷笑道：“江南四狗怎么不敢进来见我？！”\n", me, ob );
		return 1;
	}
	else {
	message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n$n笑道：“不用客气，你来解我寂寞，可多谢你啦。”\n", me, ob );
	message_vision("$N道：“不敢。”\n$n点了点头，说道：“我只想瞧瞧你的剑法，并非真的过招，再说，我也未必能胜得了你。”\n\n", me, ob);
    command("笑傲江湖中老子剑法天下第一，找我比剑？找死！\n");
	command("enable sword damo-jian");
	say(HIR"\n任我行大喝一声：“少林派达摩剑法"NOR"「"HIR"达摩三绝剑"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第一招。\n");
	command("enable sword taiji-jian");
	say(HIR"\n任我行大喝一声：“武当太极剑法"NOR"「"HIG"三环套月"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第二招。\n");
	command("enable sword huifeng-jian");
	say(HIR"\n任我行大喝一声：“峨嵋派回风拂柳剑"NOR"「"HIW"燎原百击"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第三招。\n");
	command("enable sword songshan-jianfa");
	say(HIR"\n任我行大喝一声：“嵩山派嵩山剑法"NOR"「"HIM"龙吟凤翔"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第四招。\n");
	command("enable sword taishan-jianfa");
	say(HIR"\n任我行大喝一声：“泰山派泰山剑法"NOR"「"HIY"岱宗如何"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第五招。\n");
	command("enable sword huashan-jianfa");
	say(HIR"\n任我行大喝一声：“华山派华山剑法"NOR"「"MAG"夺命连环三仙剑"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第六招。\n");
	command("enable sword hengshan-jianfa");
	say(HIR"\n任我行大喝一声：“衡山派衡山剑法"NOR"「"CYN"衡山云雾回风十三式"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n第七招。\n");
	command("enable sword hengshan-jianfa");
	
	say(HIR"\n任我行大喝一声：“恒山派恒山剑法"NOR"「"WHT"绵里藏针"NOR"」！”\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
    say(HBMAG"\n突然任我行发出一声巨吼，震的耳朵一阵阵发麻，一个不注意。。。。。\n\n"NOR);
	say("\n任我行叹了口气，说道：“还是没过八招。”\n");
	me->set_temp("renwoxing/bijian", 1);
	me->set("qi",-1);
	me->delete_temp("quest/xxdf/start");
	me->set_temp("quest/xxdf/startlass",1);
		return 1;
	         }
          }
         }
        }
       }
      }
     }
   }
  }
	return 1;
}

void attempt_apprentice(object ob)
{
	mapping fam;
    if ((int)ob->query("quest/xxdf/pass",1) < 1)
	{
		command("say 我是不轻易收徒的。");
		return;
	}
    if (!(fam = this_player()->query("family")) || fam["family_name"] !="日月神教"){
             command("thank "+ (string)ob->query("id"));
             command("say 你与本派素无来往，我不会收你为徒的？");
             return 0;
        }
    if ((int)ob->query_skill("xixing-dafa",1) < 450)
	{
		command("say 在吸星大法上，" + RANK_D->query_respect(ob) +
			"是否还应该多下点功夫？");
		return;
	}
   
	    command("say 好吧，既然你我如此投缘，老夫就收下你了。");
        command("老夫收得如此良徒，东方不败小儿你的报应来拉!");
	    command("recruit " + ob->query("id"));
	    message_vision(
HIG"\n$N拍着胸膛道：“任老先生，你一世英雄了得，何苦在这地牢之中和腐"+
"土同朽？只须你答允收我为徒，在下言出如山，自当助你脱困。我想老"+
"先生经过一番比剑，当年的豪情胜概，不免在心中又活了起来罢？外边"+
"天地多么广阔，你老爷子出得黑牢，普天下的男女老幼，你要杀哪一个"+
"便杀哪一个，无人敢与老爷子违抗，岂不痛快之极？”\n"NOR, ob);
ob->set("title",HIR"日月神教任我行亲传弟子"NOR);
  
}
//屏蔽不能学的武功
int prevent_learn(object ob, string skill)
{
	if (skill == "tianmo-jian"
	    ||skill == "taiji-jian"
		||skill == "huifeng-jian"
		||skill == "tanshan-jianfa"
		||skill == "hengshan-jianfa"
		||skill == "songshan-jian"
		||skill == "huashan-jianfa"
		||skill == "poison"
	    ||skill =="damo-jian")
		return 1;
	return 0;
}
int ask_ronggong() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关吸星大法融功绝技的真正奥妙。\n"NOR, me, this_object());
	if(!me->query_temp("xixing/killeddf"))
	{
		command("?");
		command("say 你不杀了东方这娘们了么，还来聒噪什么？"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/xxdf/pass")==2)
	{
		command("?");
		command("say 你开始发癫痫了，明明解开了，还来啰嗦什么？"NOR);
		me->set("title",HIC"日月神教"HIB"吸星大法传人"NOR);
		me->set("mytitle/quest/xxdftitle",HIC"日月神教"HIB"吸星大法传人"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(!me->query("quest/xxdf/pass"))
	{
		command("?");
		command("say 你连吸星大法是什么东西都不知道，还想妄谈融合？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	
	if(me->query("quest/xixing/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/xixing/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("xixing-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前吸星大法还没大飞，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("quest/xixing/time",time());
	me->set("quest/xixing/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say 吸星大法乃我神教最高绝技，既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	tell_object(me,HIY"\n你按照教主任我行的指点，对吸星大法彻底融合的真正奥妙似乎有些心得。\n"NOR);
	tell_object(me,HIW"\n你按照任我行的行功路线，开始对早期吸纳的各种功法进行融功，意图彻底融合。\n"NOR);
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	me->delete_temp("xixing/killeddf");
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	if(i<3&&random(me->query("kar"))>28)
	{
		tell_object(me,HIY"\n你按照教主任我行的指点，丹田常如空箱，恒似深谷，空箱可贮物，深谷可容水。若有内息，\n"+
			"散之于任脉诸穴~丹田有气，散之任脉，如竹中空，似谷恒虚~丹田内息，散于四肢，膻中之气，分注八脉。\n"NOR);
		tell_object(me,HIW"\n只觉起自丹田，经过命门，顶天庭，聚集于膻中，然后散于四肢，手上的力道似乎大了很多。\n"NOR);
		tell_object(me,HIC"\n这一次的散功和先前所有相比有了明显的不同，先前散功又回聚集在丹田，而这次的散功却真正散掉。\n"NOR);        
		tell_object(me,MAG"\n你觉得浑身异常舒服，暖洋洋的宛如冬日暖阳，以此为始，循环往复，你彻底掌握了吸星大法的融功。\n"NOR);
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/xxdf/pass",2);
		me->set("title",HIC"日月神教"HIB"吸星大法传人"NOR);
		me->set("mytitle/quest/xxdftitle",HIC"日月神教"HIB"吸星大法传人"NOR);
		log_file("quest/xxdfrg", sprintf("%8s(%8s) 失败%d次后，彻底领悟吸星大法的融合。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/xixing/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/xixing/fail",1);
		command("buddha");
		tell_object(me,HIR"你听了教主任我行的指点,经脉运行，则稍一运使，便互相冲突。内脏如经刀割。一个忍受不住，哇地吐出一口鲜血。\n"NOR);
		tell_object(me,HIY"这一次的运行，耗费了你极大的精力和内力，最终没有能融汇贯通，你趴自哪儿，浑身没有一丝力气。\n"NOR);
		me->unconcious();
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/xxdfrg", sprintf("%8s(%8s) 吸星大法融功绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/xixing/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}

int ask_dongfang() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	//message_vision(HIC"$N向$n请教有关吸星大法融功绝技的真正奥妙。\n"NOR, me, this_object());
	
	if(!me->query("quest/xxdf/pass")||me->query("family/family_name")!="日月神教")
	{
		command("?");
		command("say 你连吸星大法是什么东西都不知道，焉能杀掉东方不败这个娘们？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query_skill("xixing-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前吸星大法还没大飞，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	command("say 哼！东方不败虽然夺取了我的教主之位，但我却甚是佩服他，属于我最佩服的三个人第一人。");
	tell_object(me,HIY"\n若想习得吸星大法的融功，你最好给我把东方不败给我杀了，否则，别在这啰嗦。\n"NOR);
	me->set_temp("xinxing/askren",1);
	return 1;
}
int ask_xxdf() 
{
	object me = this_player();
	object ob;
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N一脸谄媚，满脸菊花灿烂绽放，向$n请教有关吸星大法拓本的相关问题。\n"NOR, me, this_object());
	if (present("xixing miji",me))
	{
		command("?");
		command("say 你身上不是有一本么，问我这个问题干嘛？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(!me->query("quest/xxdf/pass"))
	{
		command("?");
		command("say 你连吸星大法是什么东西都不知道，问我这个问题干嘛？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
    ob = new("/d/meizhuang/obj/xixing-book");
    ob->move(me);   
	
	command("say 哼！在地牢里不是留有吸星大法的秘籍么，干嘛不好好学习，做什么都丢三落四的，小心我开除！");
	tell_object(me,HIY"\n任我行从怀里摸出一本秘籍拓本，塞入你的怀里。\n"NOR);
	//me->set_temp("xinxing/askren",1);
	return 1;
}

//天魔掌绝技
int ask_ruozhuo() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关天魔掌中【若拙实巧】绝技的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="日月神教")
	//||me->query("family/master_id")!="ren woxing"
	{
		command("?");
		command("say 你不是我弟子，还来聒噪什么？"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hmy/tmzf/ruozhuo/pass"))
	{
		command("?");
		command("say 你已经懂得了若拙实巧的道理，还来啰嗦什么？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	
	if(me->query("quest/hmy/tmzf/ruozhuo/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/hmy/tmzf/ruozhuo/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里了，明天吧。");
		return 1;
	}
	if(me->query_skill("tianmo-zhang",1)<450||me->query_skill("strike",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前掌法还没大飞，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("quest/hmy/tmzf/ruozhuo/time",time());
	//me->set("tmzf/combat_exp",me->query("combat_exp")); 
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	command("heng "+me->query("id"));
	command("say 天魔掌若拙实巧乃我神教掌法最高绝技，既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	tell_object(me,HIY"\n你按照教主任我行的指点，对天魔掌若拙实巧的奥义开始思考，变听变比划，甚是投入。\n"NOR);
	
	command("whisper "+me->query("id")+" 慢就是快，快就是慢，快慢间转换存乎一心，因敌而变。\n");
	command("smile "+me->query("id"));
	
	if(i<5 
		&& random(me->query("kar"))>=25
		&&me->query("kar")<31)
	{
		tell_object(me,HIY"\n你按照教主任我行的指点，经脉流转不息，手上时松时紧，变幻不定，看似笨拙不堪，实则灵巧之极，\n"+
			"其招朴实无华，看似笨拙却甚难招架。此招能以浑厚的掌力迫使对手难于进攻。\n"NOR);
		
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/hmy/tmzf/ruozhuo/pass",1);
		log_file("quest/tmzf", sprintf("%8s(%8s) 失败%d次后，领悟若拙实巧的奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/hmy/tmzf/ruozhuo/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hmy/tmzf/ruozhuo/fail",1);
		command("heng ");
		command("kick "+me->query("id"));
		tell_object(me,HIR"你虽然看到了任我行的指点,但死活领悟不了各种奥秘。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/tmzf", sprintf("%8s(%8s) 天魔掌若拙实巧绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/hmy/tmzf/ruozhuo/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
//七弦无形剑绝技--千变万化

int ask_qianbian() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关七弦无形剑中【千变万化】绝技的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="日月神教"||me->query("family/master_id")!="ren woxing")
	{
		command("?");
		command("say 你不是我弟子，还来聒噪什么？"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hmy/qxwxj/qianbian/pass"))
	{
		command("?");
		command("say 你已经懂得了千变万化的道理，还来啰嗦什么？"NOR);
		command("kick "+me->query("id"));		
		me->set("mytitle/quest/qbwhtitle",HIC"千变万化"HIB"万变不离其宗"NOR);
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	
	if(me->query("quest/hmy/qxwxj/qianbian/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/hmy/qxwxj/qianbian/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里了，明天吧。");
		return 1;
	}
	if(me->query_skill("qixian-wuxingjian",1)<450||me->query_skill("sword",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前七弦无形剑还没大飞，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("quest/hmy/qxwxj/qianbian/time",time());
	//me->set("tmzf/combat_exp",me->query("combat_exp")); 
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	command("heng "+me->query("id"));
	command("say 七弦无形剑实巧乃我神教剑法最高绝技，既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	tell_object(me,HIY"\n你按照教主任我行的指点，对七弦无形剑千变万化的奥义开始思考，变听变比划，甚是投入。\n"NOR);
	
	command("whisper "+me->query("id")+" 慢就是快，快就是慢，快慢间转换存乎一心，因敌而变。\n");
	command("smile "+me->query("id"));
	
	if(i<3 && random(me->query("kar"))>=28&&me->query("kar")<31)
	{
		tell_object(me,HIY"\n你按照教主任我行的指点，经脉流转不息，手上时松时紧，变幻不定，看似笨拙不堪，实则灵巧之极，\n"NOR);
		
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/hmy/qxwxj/qianbian/pass",1);
		me->set("title",HIC"千变万化"HIB"万变不离其宗"NOR);
		me->set("mytitle/quest/qbwhtitle",HIC"千变万化"HIB"万变不离其宗"NOR);
		log_file("quest/qxwxjqianbian", sprintf("%8s(%8s) 失败%d次后，领悟七弦无形剑千变万化的奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/hmy/qxwxj/qianbian/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hmy/qxwxj/qianbian/fail",1);
		command("heng ");
		command("kick "+me->query("id"));
		tell_object(me,HIR"你虽然看到了任我行的指点,但死活领悟不了各种奥秘。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/qxwxjqianbian", sprintf("%8s(%8s) 千变万化绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/hmy/qxwxj/qianbian/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}