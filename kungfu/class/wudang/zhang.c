// zhang.c ������
// Modified by Lklv for raozhi Quest @@
// Update By lsxk@hsbbs for taiji_quest 2007/6/3
// By Spiderii@yt ����yttlg quest
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me_1();
string ask_me_2();
string ask_me_3();
string ask_me_4();
string ask_me_5();
string ask_raozhi();
string ask_no_save();
string ask_jueyuan();
string ask_jiuyang();
string ask_tjsg();
string ask_taiji();
string ask_tjj();
string ask_jianjue();
int thinking_tjq(object me);
int ask_yttlg();
string ask_jyzj();
#define NO_SAVE_ID "/log/skills/no_lifesave"

void create()
{
        object weapon;
        set_name("������", ({ "zhang sanfeng", "zhang", "sanfeng" }));
        set("nickname", "��������");
        set("long",
                "�������䵱�ɿ�ɽ���桢�������ֵ�̩ɽ�������������ˡ�\n"
                "��һ���ۻ�İ�ɫ���ۣ����ޱ߷���\n"
                "��ĸߴ��������꣬������⣬��ü�԰ס�\n");
        set("gender", "����");
        set("age", 100);
        set("attitude", "peaceful");
        set("str", 33);
        set("int", 45);
        set("con", 33);
        set("dex", 33);
        set("per", 28);
        set("unique", 1);
        set("no_get", 1);
		set("max_qi", 95000);
        set("max_jing", 10500);
        set("eff_jingli", 9000);
        set("max_neili", 93000);
        set("neili", 93000);
        set("jiali", 200);
        set("combat_exp", 1000000000);
        set("shen", 464000);
        set("quest/wd/yyzq/taiji/pass",1);
		set("quest/tjq/taiji","pass");

		set("chat_chance_combat", 50);
		
        set("chat_msg_combat", ({
                (: exert_function, "yinyun" :),
                (: perform_action, "cuff.dongjing" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "cuff.an" :),
                (: perform_action, "cuff.yinyang" :),
                (: perform_action, "cuff.gangrou" :),
                (: perform_action, "sword.sanhuan" :),
                (: perform_action, "cuff.zhannian" :),
                (: perform_action, "sword.lian" :),
				(: perform_action, "sword.sanhuan" :),
                (: perform_action, "cuff.luanhuan" :),
                (: perform_action, "cuff.ji" :)
        }));
        set_skill("force", 2550);
        set_skill("yinyun-ziqi", 2551);
        set_skill("dodge", 2550);
        set_skill("tiyunzong", 2550);
        set_skill("cuff", 2550);
        set_skill("taiji-quan", 2551);
        set_skill("parry", 2550);
        set_skill("sword", 2550);
        set_skill("taiji-jian", 2551);
        set_skill("taoism", 220);
        set_skill("blade", 2550);
        set_skill("zhenwu-qijiezhen", 200);
        set_skill("literate", 500);
        set_skill("zhenshan-mianzhang", 2550);
        set_skill("strike", 2550);
        set_skill("wudang-quan", 2550);
        set_skill("xuanxu-daofa", 2550);
        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-mianzhang");
        map_skill("blade", "xuanxu-daofa");
        prepare_skill("cuff", "taiji-quan");
        set("inquiry", ([
                "���佣" : (: ask_me_1 :),
                "����" : (: ask_me_2 :),
                "̫��ȭ��" : (: ask_me_3 :),
                "̫��ȭ����" : (: ask_taiji :),
		        "��ɽ" : (: ask_me_4 :),
                "��ɽ" : (: ask_me_4 :),
                "�̻�" : (: ask_me_5 :),
         //		"�ж�" : (: ask_no_save :),
                "��ָ�ὣ" : (: ask_raozhi :),
				"̫����" : (: ask_tjsg :),
				"��Զ��ʦ" : (: ask_jueyuan :),
				"������" : (: ask_jiuyang :),
				"̫��������" : (: ask_tjj :),
                "����������" : (: ask_yttlg :),
				"̫������" : (: ask_jianjue :),
				"�����澭" : (: ask_jyzj :),
        ]));
        set("wan_count", 1+random(2) );
        create_family("�䵱��", 1, "��ɽ��ʦ");
        set("class", "taoist");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 100);
        set_temp("apply/armor", 70);
        set_temp("tj/taiji", 1);
        set("taiji_quest", 1);
        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("sword/zhenwu-jian"));
                if (!weapon) weapon = new(BINGQI_D("zhujian"));
                weapon->move(this_object());
                weapon->wield();
                carry_object("/d/wudang/obj/white-robe")->wear();
                carry_object("/d/wudang/obj/daolv")->wear();
        }
}

void init()
{
        object ob;

        ::init();
        ob = this_player();
        if (interactive(ob = this_player()) && visible(ob) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

}

void greeting(object me)
{
        mapping myfam;
        int shen;

        if (!me || !present(me)) return;

        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

        myfam = (mapping)me->query("family");
        shen = me->query("shen");

        if (me->query("taiji_zsf") >= 6 && me->query("taiji_quest"))
                me->delete("taiji_quest");

        if(!myfam) return;
        else if(myfam["family_name"] != "�䵱��")
                command("say �ϵ��ڴ����ޣ���ʲô�����λ"+RANK_D->query_respect(me)+"�����ˣ�");
        else if(shen < 0 && shen > -15000)
                command("say  ��ѧ�ù���Ҫ���������ˣ���Ŀ��΢��а�������Ƕ�ȥ����������֮�°ɡ�");
        else if(shen < -15000){
                command("say ����Ϊ�䵱���ӣ����ز�����������Ͳ��������䵱�����ˡ�");
                command("expell " + me->query("id"));
        }
        else command("nod");
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");
        if ((!fam || fam["family_name"] != "�䵱��")
         && ob->query("expell/family_name") != "�䵱��"){
                command("say "+RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if ((int)ob->query_skill("yinyun-ziqi", 1) < 350) {
                command("say ���䵱�����ڼ��书���������ڹ��ķ��������������ûС�ɣ�����Ŭ����");
                command("say " + RANK_D->query_respect(ob) + "�Ƿ�Ӧ�����������϶��µ㹦��");
                return;
        }
        if ((int)ob->query("shen") < 2000000) {
                command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����(2M)");
                return;
        }
		if (!ob->query("quest/wd/dichuan"))
		{
			    command("say ����Ȼ�����䵱���ӣ������ǵմ����㻹����ȥ������Ҷ������ض�����");
                command("say ��λ��" + RANK_D->query_respect(ob) +"ֻ�л�õմ������ʸ����Ϊʦ��");
                return;

		}
        if(fam["family_name"] == "�䵱��" 
			&& ob->query_skill("juehu-shou",1)>350 
            && ob->query_skill("yinyun-ziqi",1)<351 
            && random(10)< 2
			&& ob->query("juehu_nouse")<1){
                command("look " + ob->query("id"));
                message_vision(HIY"ֻ��������΢΢������һ����\n"NOR, ob);
                write(HIR"���Ȼ��������΢΢һ�ȡ�\n"NOR,ob);
                ob->set("juehu_nouse",1);
                command("say ���䵱������������ͽ���ϣ��ҷ�ס�������Ѩ���Ǿ����ֹ����������Ժ�Ҫ�����ˡ�");
        }
		if (ob->query_int() < 50) {
                command("say ���䵱���书ȫ�ӵ��������");
                command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
                command("say " + RANK_D->query_respect(ob) + "�����Բ���50������Ǳ�����ڣ�������ذɡ�");
                return;
        }
        command("say ����������������");
        command("say �벻���ϵ��ڴ���֮�꣬���ٵ�"+ob->name(1)+"����һ������֮�ţ����ǿ�ϲ�ɺء�");
        command("recruit " + ob->query("id"));
}

void kill_ob(object me)
{
        if(!wizardp(me))
                command("crazy " + me->query("id"));
        if(!this_object()->query_temp("weapon"))
                command("enable parry taiji-quan");
        command("exert taiji");
        ::kill_ob(me);
}

void unconcious()
{
          command("say ƶ������ʼ���������죬�������ˣ�");
        ::unconcious();
}
//̫��������
string ask_jianjue()
{
	object me = this_player();
	mapping fam;

     if (!(fam = me->query("family")) || fam["family_name"] !="�䵱��"||fam["master_name"] !="������")
           return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
	 if ( time()-me->query("quest/wd/tjj/jianjue/time")<86400)
     {
		command("shake "+ (string)me->query("id"));
		return "���ĸ����꣬���Ƶ��ɧ���ң����������̫����������!\n";
	  }
	
	 if ( me->query("quest/wd/tjj/jianjue/pass"))
		return "�㲻���Ѿ������̫��������������?!\n";
	 if ((int)me->query_skill("taiji-jian",1)<500)
		return "��̫��������δ����,������������Ī���̫������?\n";
	 if ((int)me->query_skill("yinyun-ziqi",1)<500)
		return "��̫��������Ҫ�����������������ܷ���,�㻹���Ƚ����ŵ������������ϰ����!\n";
	 if ((int)me->query_skill("taoism",1)<200)
		return "��Ե�ѧ�ķ�������̫��,�����ڴ���̫����������,ֻ�Ầ������ʱ�߻���ħ!\n";
	 if (random(me->query("kar"))>25
		&&random(me->query_int(1))>35)
	 {
		 command("pat "+me->query("id"));
		 command("say �������ˣ���̫������....����");
		 command("whisper "+me->query("id"));
		 command("say ��Ȼ��ͨ�������Ž������ɣ��Ժ�ҪΪ�Ҵ��䵱�������塣");
		 me->set("quest/wd/tjj/jianjue/pass",1);
		 return "�䵱̫���������ĺ��ľ���Բת���⣬���ϲ���..";
	 }else{
		 command("disapp "+me->query("id"));
		 command("say ��̫������ȫ�����ԣ����⼸���ǲ��ǹ���û���ã�");
		 command("say ��Ȼ����˼򵥵Ľ����������ˣ����Ǳ����ˣ�");
		 me->set("quest/wd/tjj/jianjue/time",time());
		 me->add("quest/wd/tjj/jianjue/fail",1);
		 return "�ߣ��Ҵ��䵱�����Ǻ���Ҫ�ġ�\n";
	 }
	
}
string ask_taiji()
{
	object me = this_player();
	mapping fam;

     if (!(fam = me->query("family")) || fam["family_name"] !="�䵱��"||fam["master_name"] !="������")
           return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
	 if ( time()-me->query("quest/tjq/time")<86400)
     {
		command("shake "+ (string)me->query("id"));
		return "���ĸ����꣬���Ƶ��ɧ���ң����������̫��ȭ��!\n";
	  }
	 if (!me->query("helpwd/fightxm")&&!me->query("mwd/over"))
	 {
		command("shake "+ (string)me->query("id"));
		return "�ɹ��������䵱���㵱ʱ���Ķ�����Ϊ�䵱���ӵ�Ϊ�䵱�������ף�!\n";

	 }
	 if (me->is_busy())
	 {
		 command("say ������æµ��\n");
		 return "�ĸ����꣬�����䵱�ķ���ɻ䣡\n";
	 }

	 if ( me->query("quest/tjq/taiji")=="pass")
		return "�㲻���Ѿ������̫����������?�м�Ҫ��������,���ɵ�����ҫ!\n";
	 if ((int)me->query_skill("taiji-quan",1)<500)
		return "��̫��ȭ����δ����,������������Ī���̫������?\n";
	 if ((int)me->query_skill("cuff",1)<500)
		return "�����ȭ������δ����,������������Ī���̫������?\n";
	 if ((int)me->query_skill("yinyun-ziqi",1)<500)
		return "��̫��������Ҫ�����������������ܷ���,�㻹���Ƚ����ŵ������������ϰ����!\n";
	 if ((int)me->query_skill("taoism",1)<200)
		return "��Ե�ѧ�ķ�������̫��,�����ڴ���̫����������,ֻ�Ầ������ʱ�߻���ħ!\n";
	 if ((int)me->query("str")<40)
		return "����������������̫�ͣ�����40,�����ڴ���̫��ȭ��������,ֻ�Ầ������ʱ�߻���ħ!\n";
		command("nod "+ (string)me->query("id"));
		command("say ����,"+ (string)me->query("name") +"��̫������һ��������죬�Ծ��ƶ�������ɸյĸ����\n����ν�ȷ������ˣ��󷢶����˽��ľ����������");
        command("say ̫�����򣬴�������ʼ����Խ��Խ����̫��������ʱ������ȴ�����谭̫��������һ�����أ���ʱ��\nϰ���������������̫��\n��ν��ʽ���������壬���ѿ�����̫����ʽ�ˡ��顱�У�̫������֮��ȴ�����еľ��磡");
		command("say ���У����������˴�����������������䣬�����������̫������");
		command("say ̫��������������У������ж�����Χ�ơ����ۣ����������ɣ������⣬��������˸��ֶ�����\nֻ�����������������ԣ����ܽ�̫�����������ط��ӳ�����");
		command("say "+ (string)me->query("name") +"���������ô��");
     
	  tell_object(me,MAG"\n�㿪ʼ����Ļ����������һ��һʽ����\n"NOR);
      me->start_busy(999);              
      remove_call_out("thinking_tjq");
      call_out("thinking_tjq",5, me );
	  return "";
}

int thinking_tjq(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_tjq")<(5+random(3)))
    { 
	  me->add_temp("try_tjq",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ�������������̫��ȭ��һ��һʽ...\n"NOR);
      else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_tjq");
	  call_out("thinking_tjq",3+random(3), me);
  } else
   {  
	  me->delete_temp("try_tjq");
      total = me->query("str");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
      i=random(j);

     if (i < 2 
		&& random(me->query("kar"))>28
		&& random(total) >= 40) 		 
     {
       
          tell_object(me,HIM"$N�����������ָ�㣬������ʽ��ʼ��һ��һ����������������������ˮ��\n"NOR);
          message_vision(HIC"$N�������ɣ���Ȼ�����Ȼ��������ת�糤����ӣ����ϲ������⾳����\n"NOR,me); 
          tell_object(me,HIR"$N�ֺ�Ȼ������̫��ȭ��������죬�����˵ľ��ϣ�����̫��ȭ����ʶ���ͬ��\n"NOR);
		  tell_object(me,HIY"$N���ڶ�����̫��ȭ�ռ��������أ�����������Ц��ԭ����ˣ�ԭ����ˣ�\n"NOR);
		  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�̫������������һ��ǰ��δ�е��¾�\n"NOR);
		  command("haha ");
		  command("chat ��ϲ"+me->query("name")+"�Ѿ�����̫��ȭ���⣬������̫��ȭ���⡣");
          me->set("quest/tjq/taiji", "pass" );
          me->set("title",HIC"̫��ȭ�洫"NOR);
		  me->set("mytitle/quest/tjqtitle",HIC"̫��ȭ�洫"NOR);
          log_file("quest/taijiquan", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪̫��ȭ���ء���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/tjq/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
        }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
		 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷����̫���������ڣ�����һ��Īչ��\n"NOR,me);
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ���̫��ȭ��������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/taijiquan", sprintf("%s(%s) ����̫��ȭ����ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/tjq/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/tjq/fail",1);
         me->set("quest/tjq/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/tjq/time",time());
        }

     }
   return 1;
}



string ask_me_1()
{
        object me=this_player();
        if (me->query("family/family_name") != "�䵱��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";

        command("pat "+ me->query("id"));
           return "�˽��˱�����ɽ֮��������������������ܷ��Ľ��㱣�ܣ�\n";
}

string ask_me_2()
{
        object me=this_player();
        if (me->query("family/family_name") != "�䵱��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
        command("thumb "+ me->query("id"));
           return "��ѹ�Ů�����ҵ�����������������ͨ�����飡�㵽������ʱ�����ĸ����Ұɡ�\n";
}
string ask_me_3()
{
        mapping fam;
        string msg;
        object me=this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="�䵱��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
        if (fam["master_name"] !="������"){
                command("pat "+me->query("id"));
                return "̫��ȭ�������ڻ��޷���⡣\n";
        }

        if(me->query("taiji_quest")){
                if(me->query("taiji_quest") <= me->query("taiji_zsf"))
                        return "�Ҳ����Ѿ����������𣿿�ȥ��ϰ�ɡ�\n";
                if(me->query("taiji_quest") == 1) msg = " ˳��ᶥ�����ɣ������������ɳţ�������������������ָץ�����乭��\n";
                if(me->query("taiji_quest") == 2) msg = " �ٲ��������ڼ꣬Ī�̶���һ���У�����������ʵ��������Ԣ�º��컹��\n";
                if(me->query("taiji_quest") == 3) msg = " �����������ڹ����߹�������������־�������ͣ���Ӧ�������ͨ��\n";
                if(me->query("taiji_quest") == 4) msg = " �������ֽ��򳤣�һ�𲻼������أ������ֿ�Է��ƣ�������ǧ�˻�����\n";
                if(me->query("taiji_quest") == 5) msg = " ���ἴ�ռ����飬������˿����������չ���������ܣ�����������è�С�\n";
                if(me->query("taiji_quest") == 6){
                        msg = " ���ļ����ķ����������⿿б�ǳɣ�Ǭ������˰��ԣ����˹��ζ����С�\n";
                        me->delete("taiji_quest");
                }

                command("nod "+me->query("id"));
                command("whisper "+me->query("id")+msg);
                tell_object(me,"������������Ľ��⣬��̫��֮���������˲��١�\n");
                me->add("max_neili", 10+random(20));
                me->add("max_jingli", 10+random(20));
                me->add("shen", random(3000)+1000);
                me->add("taiji_zsf", 1);
                return "���������Ҫ�����ס��\n";
        }
        return "̫��֮�������ڻ��޷���⡣\n";

}

string ask_me_4()
{
        object me=this_player();

        if (me->query("family/family_name") != "�䵱��")
                return RANK_D->query_respect(me)+"ʩ����ȻҪ��ɽ��ƶ���Ͳ�Զ���ˡ�";
        command("pat "+ (string)me->query("id"));
        command("say �����ն���Ϊ��������Ҫ��Ϊ������Щ����������¡�");
        me->set_temp("jian_quest",1);
        return "�ǵ�Ϊʦ�Ľ̻壬��Ϊ���������Ҷ������㣡��\n";
}

string ask_me_5()
{
        object me=this_player();
        object ob;
        string ob_desc;
        int i,j;

        i = me->query("combat_exp")/ 200000;
        if (i < 50)  i = 50;
        if (i > 100)  i = 100;
        j = me->query_skill("taiji-jian",1)/ 5;
        if (j < 50)  j = 50;
        if (j > 100)  j = 100;

        if (me->query("family/family_name") != "�䵱��")
		return RANK_D->query_respect(this_player())+"����ƶ�����ӣ���̸�̻壿";
        
        if (! me->query_temp("jian_quest") || me->query("combat_exp")<100000)
        	return "��Ϊ���������Ҷ������㣡ȥ�ɡ�\n";

        if (present("songwen gujian",me))
            return "��סΪʦ�Ļ������������壬����Ľ�һ��Ҫ�պá�";

	    command("nod "+ (string)me->query("id"));
        command("say ���䵱���������������Կ������Ϊ���Ρ�");
        command("say �����������Ȼ���������ҵ�ϰ��֮��ȴ���洦��");
        command("say ժҶ�ɻ����Կ����ˡ���֦��Ҷ���Կ�Ϊ��������ǧ����ľ�Ƶô˽����䲻��ɽ���Īа��");
        command("say ���������ȴҲ���������졢�������ǵ�Ϊʦ�Ľ̻壬ȥ�ɡ�");
        command("party* "+"wave "+(string)me->query("id"));
        me->delete_temp("jian_quest");
        me->add("shen",100+random(100));

        ob=new(BINGQI_D("sword/sw_jian"));

        ob_desc =
		sprintf("���Ͽ���һ��С�֣��䵱�ز�,������������%s(%s)����,�����������������\n",me->query("name"),me->query("id"));

        ob->set("long",ob_desc);
        ob->set("rigidity", 5);
        ob->set("weapon_prop/parry", i);
        ob->set("weapon_prop/sword", j);
        ob->set("owner", me->query("id"));
 
        ob->move(me);
        message_vision("\n$N����$nһ�ѹ��ⰻȻ��ľ����\n", this_object(), me);

        return "�����Ϊ֮��\n";
}
int accept_object(object who, object ob)
{
        object sword, me;
        mapping fam;
        me = this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="�䵱��"){
             command("thank "+ (string)who->query("id"));
             command("say ���뱾��������������֪Ϊ������˺���");
             return 0;
        }

        if (fam["generation"] == 2)
        if ((string)ob->query("id") == "tie luohan"){
            command("goodkid "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            if (present("zhenwu jian", me)){
            	  command("give zhenwu to "+(string)who->query("id"));
                  command("say ��������⽣Ϊ���������ұ�ȡ��������");
                  return 1;
            }
            else{
                  sword = unew(BINGQI_D("sword/zhenwu-jian"));
                  if (!clonep(sword)) {
                    command("say �������Ϻ�Ϳ�ˣ�����֪�����ˡ�");
                    return 1;
                  }
                  sword->move(this_player());
                  command("say ��������⽣Ϊ���������ұ�ȡ��������");
                  return 1;
            }
        }
        command("? "+ (string)who->query("id"));
        command("say ���첻���ϵ������գ�����ʲô��ѽ��");
        return 0;
}

void destroying(object obj)
{
    	if (!obj) return;
    	if (userp(obj)) command("drop "+obj->parse_command_id_list()[0]);
    	else destruct(obj);
}

string ask_no_save()
{
        object ob, me = this_player();
        string *no_save, id, tmp;

        me->add_busy(1);
        if (me->query("family/family_name") != "�䵱��")
                return RANK_D->query_respect(this_player())+"ʩ����������ʲô��˼��";

        command("hmm "+ (string)me->query("id"));

        if( me->query("combat_exp") < 1000000 )
        	return "���ŵ��ӣ�ֻҪ�е���������ʲô��\n";

        if( me->query("last_kzf") )
        	return "����Ϊ��������Ҫ������ʦ�ţ�\n";

        if( !stringp(id = me->query("last_killer")) )
        	return "���ŵ��ӣ�ֻҪ�е���������ʲô��\n";

        if( sscanf(id, "%s(%s)", tmp, id) != 2 )
        	return "���ŵ��ӣ�ֻҪ�е���������ʲô��\n";

        id = lower_case(id);

        ob = LOGIN_D->find_body(id);
        if ( !ob || !userp(ob) )
        	return "������˭����Ҫ�������������\n";

        if( ob->query("family/family_name") == "�䵱��" )
        	return "ͬ��ʦ�ֵܣ�Ӧ�ú����ദ�������������ϵ�ʮ�����İ���\n";

        if( file_size(NO_SAVE_ID) > 0 )
        	no_save = explode(read_file(NO_SAVE_ID), "\n");
        else no_save = ({});

        if( member_array(id, no_save) != -1 )
        	return "�����ϵ��Ѿ�֪���ˣ����Ժ󿴼�ҪС��Ӧ����\n";
        no_save += ({ id });
	    id = implode(no_save, "\n") + "\n";

        write_file(NO_SAVE_ID, id, 1);

        command("nod");
        return "�����ն�ҪС��Ӧ����һ��Ҫ�ǵ�Ϊʦ�Ľ̻尡��\n";
}

string ask_raozhi()
{
        object me=this_player();
        if (me->query("family/family_name") != "�䵱��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";

        if (me->query("raozhi")){
        	command("knock "+me->query("id"));
		return "�����ԣ��̹���Ľ�����ô�����ˣ�";
	    }

        if (!me->query_temp("raozhi"))
		   return RANK_D->query_respect(me)+"Ϊ���д�һ�ʣ�";

	    if (me->query_skill("yinyun-ziqi", 1) < 450
	      || me->query_skill("taiji-jian", 1) < 450)
		 return RANK_D->query_respect(me)+"��������̫�����ȼ�����̫�ͣ�����450����Щ�����ڻ��޷���ᡣ";

	    if (random(10)< 6 || random(me->query("kar"))<20){
		  //me->set_temp("raozhi",3);
		  return YEL"������������ͽ�����������������˴��ż������������첻��̸��㣬����������ɡ�\n"NOR;
		}
		me->set("raozhi",1);
		command("pat "+ me->query("id"));
		command("secret "+ me->query("id"));
		return HIC"�������´���һ�н�������û���ڶ������ù��������Ҿͽ̸���ɡ�\n"NOR;
}

int ask_yttlg() 
{
	object me = this_player();
	object ob = this_object();
  if(me->query("quest/yttlg/pass")&&!me->query_skill("yitian-tulong"))
  {
	  command("? "+me->query("id"));
         command("say �úõĹ���Ϊɶ���ϵ���?�ѵ����Դ����Ÿ����ˣ�\n");
		 command("sigh "+me->query("id"));
		 me->set_skill("yitian-tulong",1);
		 command("say ������ʾһ�����������ټǲ�ס�ҾͰ�����������ˣ�\n");
		 command("disapp "+me->query("id"));
    return 1;
  }


  if(!me->query_temp("quest/yttlg/ask"))
  {
	  command("? "+me->query("id"));
         command("say ���������ʲô?");
    return 1;
  }
    me->delete_temp("quest/yttlg/ask");
    command("pat "+me->query("id"));
    message_vision(HIC"\n\n$n΢Ц�Ŷ�$N˵��������Ҫ����ϸ��!��,˵�����ִ��˱�����������!\n"NOR,me,ob); 
    remove_call_out("thinking");
		call_out("thinking",5, me, ob);
    tell_object(me,YEL"��ƴ���ػ�����������ָ�����ƣ��㿪ʼ����˼����.........\n"NOR);
    me->start_busy(2);
	  return 1;
}

int thinking(object me, object ob)
{
	int j;
	if(!me) return 0;
	j = 20;
    if(me->query("m-card-vip")) j =  19;
    if(me->query("y-card-vip")) j =  17;
    if(me->query("buyvip"))     j =  15;
    j=random(j);

  if(me->query_temp("yttlg_thinking")<(3+random(3)))
	{
		me->add_temp("yttlg_thinking",1);
    if(random(2)) tell_object(me,HIG"\n��Ŭ���ػ���ղ���������ָ������,ֻ�����ۻ�����...\n"NOR);
    else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô����Ŭ���ػ���ղ���������ָ�����ƣ����ƺ��о��������еı仯����...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��һ����ü��չ�����ӡ�\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
    me->delete_temp("yttlg_thinking");

    //   p=random(10);

    if(j<5
		&&me->query("kar")>25 
		&& me->query("kar")<31 )
    {
       tell_object(me,HIG"\n���ʱ���½��ղŵľ�����ʽ���ˣ�������ϥ���£�һ��һ����һ��һʽ��ĬĬ���䡣\n"NOR);
       tell_object(me,HIG"\n�㵱��֮���������������ݼ��֡�Ҳ��֪���˶���ʱ�򣬲Ž��Ƕ�ʮ���ֶ���һʮ����е���Ų�仯�����������С�\n");
       tell_object(me,HIG"\n��ֻ���ﲨ��������ɵ����Ӿ�Э���������ƣ�ȫ������ƮƮ�ģ��������Ƽ���һ�㡣\n");
       message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
       tell_object(me,HIR"�������������ָ��,���������������������ľ������ڡ�\n"NOR);
       me->set("quest/yttlg/pass",1);
       me->delete_temp("quest/yttlg/ask");
       me->set_skill("yitian-tulong",1);
	   log_file("quest/yttlg", sprintf(HIR"%s(%s) �ɹ��⿪��������������Դ��%d�����飺%d��\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
    }
    else
    {
       tell_object(me,HIG"\n���Ժ����ƺ�ץס��ʲô��������Ȼ���Ǻ����ס�\n"NOR);
       message_vision(HIC"\n$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n"NOR,me); 
       command("poor "+me->query("id"));
       me->add("quest/yttlg/fail",1);
       me->delete("quest/yttlg/ask");
	log_file("quest/yttlg", sprintf(HIR"%s(%s) ������������ʧ�ܡ���Դ��%d�����飺%d��\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
    }
  }
  return 1;
}
//̫���񹦿�ʼ
string ask_jueyuan()
{
    object me;
    me=this_player();
	if (me->query("family/family_name")!="�䵱��"||me->query("family/master_name")!="������")
	{
		command("say �㲻�����䵱���ӣ�����������");
		return "���ǲ����⣡";
	}
	if (!me->query("quest/wd/tjj/qianjin/pass")&&me->query("quest/tjq/taiji")!="pass")
	{
		command("say ������̫��ȭ��̫��������һ���书�������£����ܶ���������˸յ����⣿");
		command("say ̫����ȫƾһ���������ʹָ������û�дﵽ�Ǹ����磬��˵����Ҳ������");
		command("say ������Ŭ��ȥ�����ɣ��κ�һ���似ȡ��ͻ�ƺ���������Ҳ���٣�");
		command("say �Ҵ��䵱һ����ʦ�����������������Ǵ������ģ�");
		command("sigh ");
		command("disapp ");
		return "�������ڵ��޶��ĸ����꣬������̫����ɻ䰡��";
	}
    if ( !me->query("mwd/over"))
    {
		command("heng "+me->query("id"));
		command("say ����䵱��ûʲô���ף����Ҵ��䵱��������֮��ʱ�����ںδ���");
		return "��λ" + RANK_D->query_respect(me) + "��Զ���ϵ��ҵ���������ѧ��ʱ�Ķ�ʦ��\n";
    }
    if ((int)me->query_skill("yinyun-ziqi",1) < 500)
       return "���������������500�������ٽ���������\n";
	if (time()-me->query("quest/wd/yyzq/taiji/time") < 86400)
       return "������̫�ڿ���,Ҫ�����ϵ�ô����\n";
    if(me->query("quest/wd/yyzq/taiji/pass")){
            return"�㲻��ѧ��̫����������ô��������ǲƶ���ң�\n";
    }

	command("say  ��Ȼ�����Ѿ�Ϊ�Ȼ��䵱������˴�Ĺ��ͣ��Ҿ͸�������ξ�����");
    me->set_temp("tjsg/askjueyuan", 1);
       
    return "������������ѧ�գ�ʦ�Ӿ�Զ��ʦ����Զ��ʦ�������ڹ��ķ����Ա�ǿ����֮�á�\n"
			+"����������ʥ��ս���֣�������ɮ�Զ�����������ʦ�����γ��֣����ȴ����һ������\n"
			+"ʦ���������Σ��������Һ͹���Ů��һ���뿪���֣�����������һֱ������ʦ������\n"
			+"��Բ��֮ǰ���ж������Ͼ��飬���м����ž����񹦵�һЩ�ھ����ҵ�ʱ���ף���δ������\n"+
			"���ҳ���󣬷�������ʦ��˵��Щ���Ķ��Ǵ�Ħ�������������Ǵ�ģ���Щ����Ӧ����\n"
			+"���ָ�ɮ���������������񹦵�����ȴ��Ϊʦ�������й�������Ϊǿ��ģ�Ϊʦ��һ���\n"
			+"����Ӧ��˵��Դ�����ⲿ�����澭��\n";
}

//������
string ask_jiuyang()
{
    object me;
    me=this_player();
    if ( !me->query_temp("tjsg/askjueyuan"))
    {
		command("? "+me->query("id"));
		return "��λ" + RANK_D->query_respect(me) + "�����񹦲����\n";
    }
 
        command("say �ţ���Զ��ʦ���괫���ҵĲ��־����񹦣��ҵ�ʱ���������䲻�࣡\n");
        command("say �ⲿ�����澭ǣ��̫�󣬵�ʱ������ɫ��ʦ�ջ���󣬹���Ů����֮�����в����˺������ֺͶ��ҵ�����\n");
        command("say ������ʱ�Ҽǵú�������Ե���֮������������սȫ��һ�仰���������������С�\n");
		command("say Ϊʦ���˺ö��꣬����������仰���������塣\n");
		command("say �����񹦺���Ϊ���޼ɺ���ϰ�ã���ȷ��ͬ���졣\n");
		command("say ������Ϊʦ����������Ĳ�������������ʤǿ������˸յĴ����\n");
		command("say Ϊʦ�����Ź��������̫���񹦡���\n");
		command("say �Ұ���Щ����ĵö����ں�ɽ��һ��ʯ���У�������Ե����ȥ�����¡�\n");
		me->set_temp("tjsg/askjiuyang",1);
		me->delete_temp("tjsg/askjueyuan");
        return "�����񹦱���辶����������ɹ����������ھ����񹦣�\n";
}
//̫����
string ask_tjsg()
{
	  object me=this_player();
	  if (!me->query_temp("tjsg/askjiuyang"))
	  {
		command("? "+me->query("id"));
		return "��λ" + RANK_D->query_respect(me) + "̫��������˸գ������\n";
	  }
		command("say ��������ҳ������ɣ�Ϊʦ���������ҵ����ں�ɽɽ��һ�����ڸ�֪���㡣\n");
		command("say Ϊʦ�������Ķ���������̫���İ���͵�����ȥ���򣬿��Ƿ������ջ�\n");
		command("say ��·���գ��мǱ���һӦ�����\n");
        me->set_temp("tjsg/askzhang", 1);
		me->delete_temp("tjsg/askjiuyang");
		command("wave "+me->query("id"));
        return "̫���񹦱���辶�����������ڹ���Ȼ��ͬ����������ɹ����������ھ����񹦣�\n";

}
//����������֮��ɽ֮�����
string ask_jyzj()
{
	  object me=this_player();
	  if ((time()-me->query("quest/����������/time"))<86400)
	  {
		  return "����Ҫ���ƣ�������̫Ƶ���ˣ�";
	  }
	  if (me->query("quest/����������/��ɽ֮��/over"))
	  {
		  me->set("quest/����������/��ɽ֮��/time",time());
		  me->set("quest/����������/time",time());
		  return "�㲻���Ѿ�֪������";
	  }
	  
	  if (me->query("shen")<0)
	  {
		  return "�ϵ��Ҷ�������а��֮ͽһ�Ϊ���ᣬ�������ң�\n";
	  }
	  if (me->query_temp("quest/����������/��ɽ֮��/start"))
	  {
		command("? "+me->query("id"));
		return "��λ" + RANK_D->query_respect(me) + "�����Ҳ����Ѿ����㽲���˹����������ڻ�ɽ֮�۵�һ������ô����\n";
	  }
		command("say ��һ���������澭�����������еĵ�һ�ڹ��ؼ����������̫�ࡣ\n");
		command("say ��ʱ��Ҳ������żȻ�ڻ�ɽһ��һ�ε�����˵��\n");
		command("say ��ʱ��ֵ�����λ�ɽ�۽����Һ;�Զ��ʦһ��ȥ׷���������������ӡ�\n");
		command("say ����˵����ֲؾ����ȡ�����Ͼ���ʦ�����ø��𿴹ܲؾ���\n");
		command("say �Һ�ʦ��Ϊ��׷���Ȿ��һֱ׷�����ǵ���ɽ�����¡�\n");
		command("say ..........��\n");
		command("say ..........��\n");
		command("say ..........��\n");
		command("say ..........��\n");

		command("say ..........��\n");


		message_vision(HIY"$N�������ὲ����������£����÷ǳ����񣬲�֪�����������ڵ�ʱ�龳֮�С�\n"NOR,me);
        me->set("quest/����������/��ɽ֮��/start", 1);

        me->set_temp("quest/����������/��ɽ֮��/start", 1);
		me->start_busy(2);
		me->set("quest/����������/time",time()-90000);
		call_out("movetossy",2+random(5),me);

        message_vision(HIC"��˼���֮�䣬����ʱ�⵹��������������ɽ֮�ۣ�\n",me);
		return "";

}
int movetossy(object me)
{
	me->move("d/huashan/sheshen");
}

int recognize_apprentice(object who, string skill)
{
        if (! who->query("can_learn/jiuyang-shengong/wudangkaishi"))
        {
                command("say ��λ" + RANK_D->query_respect(who) + "�����ˣ�ƶ�����µ�΢����̸��ָ�㡱���֡�");
                return -1;
        }

        if (skill != "wudang-jiuyang")
        {
                command("say ����ν��֪����֣������򰲡��������书��ˡƶ�����ܽ��ڡ�");
                return -1;
        }
        return 1;
}

//̫��������

string ask_tjj()
{
	object me = this_player();
	mapping fam;

     if (!(fam = me->query("family")) || fam["family_name"] !="�䵱��"||fam["master_name"] !="������")
           return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
	 if ( time()-me->query("quest/wd/tjj/qianjin/time")<86400)
     {
		command("shake "+ (string)me->query("id"));
		return "���ĸ����꣬���Ƶ��ɧ���ң����������̫������!\n";
	  }
	 if (!me->query("helpwd/fightxm")&&!me->query("mwd/over"))
	 {
		command("shake "+ (string)me->query("id"));
		return "�ɹ��������䵱���㵱ʱ���Ķ�����Ϊ�䵱���ӵ�Ϊ�䵱�������ף�!\n";

	 }
	 if (me->is_busy())
	 {
		 command("say ������æµ��\n");
		 return "�ĸ����꣬�����䵱�ķ���ɻ䣡\n";
	 }
	 if ( me->query("quest/wd/tjj/qianjin/pass"))
		return "�㲻���Ѿ������̫������������?�м�Ҫ��������,���ɵ�����ҫ!\n";
	 if ((int)me->query_skill("taiji-jian",1)<500)
		return "��̫��ȭ����δ����,������������Ī���̫������?\n";
	 if ((int)me->query_skill("sword",1)<500)
		return "�����ȭ������δ����,������������Ī���̫������?\n";
	 if ((int)me->query_skill("yinyun-ziqi",1)<500)
		return "��̫��������Ҫ�����������������ܷ���,�㻹���Ƚ����ŵ������������ϰ����!\n";
	 if ((int)me->query_skill("taoism",1)<200)
		return "��Ե�ѧ�ķ�������̫��,�����ڴ���̫����������,ֻ�Ầ������ʱ�߻���ħ!\n";
	 if ((int)me->query("int")<40)
		return "����������Բ�����̫�ͣ�����40,�����ڴ���̫��ȭ��������,ֻ�Ầ������ʱ�߻���ħ!\n";
		command("nod "+ (string)me->query("id"));
		command("say ����,"+ (string)me->query("name") +"��̫������һ��������죬�Ծ��ƶ�������ɸյĸ����\n����ν�ȷ������ˣ��󷢶����˽��ľ����������");
        command("say ̫�����򣬴�������ʼ����Խ��Խ����̫��������ʱ������ȴ�����谭̫��������һ�����أ���ʱ��\nϰ���������������̫��\n��ν��ʽ���������壬���ѿ�����̫����ʽ�ˡ��顱�У�̫������֮��ȴ�����еľ��磡");
		command("say ���У����������˴�����������������䣬�����������̫������");
		command("say ̫��������������У������ж�����Χ�ơ����ۣ����������ɣ������⣬��������˸��ֶ�����\nֻ�����������������ԣ����ܽ�̫�����������ط��ӳ�����");
		command("say "+ (string)me->query("name") +"���������ô��");
     
	  tell_object(me,MAG"\n�㿪ʼ����Ļ����������һ��һʽ����\n"NOR);
      me->start_busy(999);              
      remove_call_out("thinking_tjj");
      call_out("thinking_tjj",5, me );
	  return "";


}

int thinking_tjj(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_tjj")<(10+random(3)))
    { 
	  me->add_temp("try_tjj",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ�������������̫������һ��һʽ...\n"NOR);
      else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_tjj");
	  call_out("thinking_tjj",3+random(3), me);
  } else
   {  
	  me->delete_temp("try_tjj");
      total = me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
      i=random(j);

     if (i < 3
		&& random(me->query("kar"))>27
		&& random(total) >= 40) 		 
     {
       
          tell_object(me,HIM"$N�����������ָ�㣬������ʽ��ʼ��һ��һ����������������������ˮ��\n"NOR);
          message_vision(HIC"$N�������ɣ���Ȼ�����Ȼ��������ת�糤����ӣ����ϲ�����̫�����⾳����\n"NOR,me); 
          tell_object(me,HIR"$N�ֺ�Ȼ������̫������������죬�����˵ľ��ϣ�����̫��������ʶ���ͬ��\n"NOR);
		  tell_object(me,HIY"$N���ڶ�����̫��ȭ�ռ��������أ�����������Ц��ԭ����ˣ�ԭ����ˣ�\n"NOR);
		  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�̫������������һ��ǰ��δ�е��¾�\n"NOR);
		  command("haha ");
		  command("chat ��ϲ"+me->query("name")+"�Ѿ�����̫�����İ��⣬������̫�������⡣");
          me->set("quest/wd/tjj/qianjin/pass", 1);
          me->set("title",HIG"̫�����洫"NOR);
		  me->set("mytitle/quest/tjjtitle",HIC"̫�����洫"NOR);
          log_file("quest/taijijian", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪̫����������ǧ��İ��ء���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/tjj/qianjin/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
        }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
		 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷����̫����������ǧ��������ڣ�����һ��Īչ��\n"NOR,me);
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ���̫������������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/taijijian", sprintf("%s(%s) ����̫����������ǧ�����ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/tjj/qianjin/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/wd/tjj/qianjin/fail",1);
         me->set("quest/wd/tjj/qianjin/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/wd/tjj/qianjin/time",time());
        }

     }
   return 1;
}

