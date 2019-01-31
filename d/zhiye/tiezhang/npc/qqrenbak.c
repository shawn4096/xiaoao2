// qqren.c 裘千仞

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "tz_job1.c"

int ask_qiubai();
string do_change();
int thinking(object me);
int ask_tiezhang();
void create()
{
        set_name("裘千仞", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", "铁掌水上漂");
        set("long",
        "他就是威震川湘的铁掌帮的帮主-铁掌水上漂裘千仞。\n"
        "他是一个白须老头，身穿黄葛短衫，右手挥着一把大蒲扇。\n");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("unique", 1);
        set("shen_type", -1);

        set("str", 35);
        set("int", 30);
        set("con", 28);
        set("dex", 35);

        set("max_qi", 9500);
        set("max_jing", 6000);
        set("max_neili", 16000);
        set("eff_jingli", 7500);
        set("jiali", 100);
        set("combat_exp", 9350000);
        set("score", 40000);
        
set_skill("axe", 450);

		set_skill("brush", 450);
		
set_skill("yingou-bifa", 450);
		
set_skill("lietian-fu", 450);

		set_skill("force", 450);
        set_skill("guiyuan-tunafa", 450);
        set_skill("dodge", 450);
        set_skill("shuishangpiao", 450);
        set_skill("strike", 450);
        set_skill("tiezhang-zhangfa", 450);
        set_skill("parry", 450);
        set_skill("literate", 180);
        set_skill("blade", 450);
        set_skill("liuye-daofa", 450);
        set_skill("tiezhang-xinfa", 200);

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "tiezhang-zhangfa");
        map_skill("blade", "liuye-daofa");
        prepare_skill("strike", "tiezhang-zhangfa");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "strike.tiezhang" :),
                (: perform_action, "strike.tianlei" :),
                (: perform_action, "strike.lianhuan" :),
                (: perform_action, "strike.heyi" :)
        }));
        set_temp("apply/armor", 80);
        set_temp("apply/damage", 80);
        set_temp("apply/attack", 80);

        create_family("铁掌帮", 14, "帮主");

        set("inquiry", ([
                       "name" : "老夫便是“铁掌水上漂”裘千仞，你问老夫姓名有什么事么？\n",
                       "here" : "这里就是铁掌帮的总坛所在，你如没事，不要四处乱走，免招杀身之祸！！！\n",
                       "上官剑南" : (: ask_qiubai :),
                       "工作" : (: ask_job1 :),
			           //"水上漂绝技" : (: ask_piao :),
			           "铁掌绝技" : (: ask_tiezhang :),
                       "工具" : "你去工具房找要吧！",
                ]));
        setup();
        carry_object("/d/tiezhang/npc/obj/mayi")->wear();
	    carry_object(ARMOR_D("buxue"))->wear();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_task","task");
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");

        if ((int)ob->query("shen") >= -50000) {
                command("hehe");
                command("say 我裘千仞可不收心慈手软的人做徒弟。");
                return;
        }
        if(fam["master_name"] == "上官剑南"){
                command("ah");
                command("grin" + ob->query("id"));
                command("say 上官帮主不是早已故世多年了嘛？");
                command("say "+RANK_D->query_respect(ob)+"原来是老帮主关门弟子啊，失敬。"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
        }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) < 120) {
                command("say 要学更为高深的武功，必须有高深的内功修为。");
                command("say " + RANK_D->query_respect(ob)+"是否还应该在归元吐纳法上多下点功夫？");
                return;
        }
        if ((int)ob->query_str() < 28) {
                command("say 想学我的铁掌掌法，必须要有足够的力量。");
                command("say 在臂力方面，"+RANK_D->query_respect(ob)+"是否还嫌差了点？");
                return;
        }
        command("say 好吧，我就收下你了。希望你苦练铁掌神功，将之发扬光大。");
        command("recruit " + ob->query("id"));
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
        ob->set("title", HIY"铁掌帮第十四代帮主门下"NOR);
        ob->set("class","brigand");
}

int ask_qiubai()
{
        say("他是我师父。我在十三岁那年曾救过他，之后他感恩图报，\n"
            "将全身武功倾囊相受。可惜十年前，他在湖北遭人围攻而死！唉！\n");
        return 1;
}

int ask_tiezhang()
{
	object me= this_player();
	if (me->query("family/family_name")!="铁掌帮") {
		command("say 铁掌绝技乃是铁掌帮不传之谜，你一个外派弟子来此作甚？");
		return 1;
	}

   if( me->query("tiezhang/pass"))
   {   
	  command("say 看样子小友已经完全掌握了铁掌绝技的要旨诀窍了。");
      command("angry ");
      return 1;
   }

	if( me->query("combat_exp",1)<5000000)
   {   
	  command("say 你的经验值太低，不能习得和领悟铁掌绝技。");
      command("sigh "+me->query("id"));
      return 1;
   }
   if( me->query("tiezhang-zhangfa",1)<350)
   {   
	  command("say 你的铁掌掌法太低，不能习得和领悟铁掌绝技。");
      command("sigh "+me->query("id"));
      return 1;
   }
    if( time()-me->query("tiezhang/time")<86400)		
   		{
				command("say 小友还是去休息一下吧。");
			    return 1;
		}

	command("say 铁掌掌法刚猛无铸，绝不比老叫花子的降龙十八掌差，而且招式上更是精妙绝伦。");
    command("say 这铁掌功夫岂同寻常？铁掌帮开山建帮，数百年来扬威中原，靠的就是这套掌法，到了上官剑南与我手里，更多化出了不少精微招术。");
    command("say 既然你对于我铁掌帮忠心耿耿，我便将这铁掌绝技传授给你，你当精心研习，勿要让五绝的其他传人横行于世！");
	command("say 看仔细了！");


    message_vision(HIR"裘千仞左掌自胸前而出，右掌跟随拍出，来势虽缓，但却同时袭到，两股强力排山倒海般压了过来，\n"
	+"你待欲退后逃避，却那里还来得及？$N上半身正面大穴却已全在掌力笼罩之下！\n"NOR+
                        HIG"裘千仞招数未完，抢上数步，又是两掌拍出，这次却是拍向$N小腹和上肢\n"+
                        HIM"$N一瞥之间均已看出，$n右手这一抓虽然凶猛，但远不及左掌那么一触即能制人死命,这才是铁掌最厉害的杀招。 \n"NOR, me);
    command("smile ");
    command("say 你可看明白了？");
    //me->delete_temp("xtg1");
       tell_object(me,HIY"\n你开始认真的回忆裘千仞的一招一式。。\n"NOR);
       me->start_busy(999);
	   me->set_temp("tzjueji/ask",10);
       remove_call_out("thinking");
       call_out("thinking",5, me );
	return 1;
}


int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("tzjueji/ask",1)>0)
    { 
	  me->add_temp("tzjueji/ask",-1);
          if(random(2)) tell_object(me,HIG"\n你认真回想着刚才裘千仞的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}

   else
   {  
	  me->delete_temp("tzjueji/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
      i=random(j-7);

     if (i == 3 
		// && random(total) >= 80 
		 && random(me->query("kar"))>=27  )
     {
       
          tell_object(me,HIM"\n你凝聚浑身劲力，引而不发，随一呼一吸，让劲力在体内流转不休！\n"NOR);
          message_vision(HIC"\n$N对如何使用铁掌掌法似乎有些了解了。”\n"NOR,me); 
		  message_vision(HIC"\n$N对如何使用水上漂轻功绝技似乎有些了解了。”\n"NOR,me); 
          tell_object(me,HIR"你对如何使用铁掌绝技融会贯通！\n"NOR);
		  command("chat* laugh ");
          command("chat 我铁掌水上漂终于有了真正的传人了！此生无憾！ ");
		  message_vision(HIW"\n$n一时高兴，看你的确是可造之材，于是将自己的轻功绝技‘水上漂’的奥秘一股脑都传授给$N。”\n"NOR,me); 
          me->set("tiezhang/pass",1);
		  me->set("tz/piao",1);
          me->set("title",HIR"铁掌"+HIW"水上漂"NOR);
          log_file("quest/tiezhang", sprintf("%s(%s) 失败%d次后，成功解开铁掌绝技。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("tiezhang/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
        }
        else
        {
         tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
         message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
         tell_object(me,HIW"\n很可惜，你本次尝试铁掌绝技秘密失败！\n"NOR);
         tell_object(me,HIY"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
         tell_object(me,HIM"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		 log_file("quest/tiezhang", sprintf("%s(%s) 解密铁掌绝技失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("tiezhang/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("tiezhang/fail",1);
         me->set("tiezhang/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("tiezhang/time",time());
        }

     }

}
