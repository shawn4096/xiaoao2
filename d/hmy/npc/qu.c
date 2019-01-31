// qu.c ����
// Finish by action@SJ 2009.1.6
// edit by sohu@xojhu add quest
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_zhen();
string ask_huayu();
string ask_book();
string ask_tmsbook();

void create()
{
	  object wt;
	  set_name("����", ({ "qu yang", "qu", "yang"}));
        set("long", "�������������ʮ����֮һ���书��ɲ⡣\n"+
		    "����������������֮�������տ��ԳƵ����ǵ�����һ��.\n");
        set("title",HIY"�������  "HIW"������ʹ"NOR);
        set("gender", "����");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 33000);
        set("max_jing", 5200);
        set("eff_jingli", 5200);
        set("jiali", 250);
        set("combat_exp", 9000000);
        set("shen", -1000);
        set("hxshenzhen",1);
		set("hmy/quest/huayu","pass");
		set("book_count",1);
		set("tbook_count",1);
		set("tmsbook_count",1);

        set_skill("strike", 450);
		set_skill("hand", 450);
        set_skill("poison", 100);
        //set_skill("blade", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
		set_skill("throwing", 450);
        set_skill("literate", 200);

        set_skill("tianmo-dao",450);
        set_skill("tianmo-zhang",450);
        set_skill("tianmo-shou",450);
		set_skill("mantian-huayu",450);
        set_skill("huanmo-wubu",450);
        set_skill("tianmo-gong",450);
        set_skill("tianmo-jue",200);
        
        map_skill("force", "tianmo-gong");
        map_skill("strike", "tianmo-zhang");
        map_skill("parry", "mantian-huayu");
        map_skill("hand", "tianmo-shou");
        //map_skill("blade", "tianmo-dao");
        map_skill("dodge", "huanmo-wubu");
        map_skill("throwing", "mantian-huayu");
        prepare_skill("hand", "tianmo-shou");
        
		set("inquiry", ([
                 "��Ѫ����" : (: ask_zhen :),
		         "���컨�����" : (: ask_huayu :),
				 "�����ַ���Ҫ" : (: ask_book :),
				  "��ħ�ַ���Ҫ" : (: ask_tmsbook :),

        ]));
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "throwing.huayu" :),
			    //(: perform_action, "blade.jingshen" :),
                (: exert_function, "tianmo" :),
				(: exert_function, "jieti" :),
        }));
	    create_family("�������", 6, "����");
        setup();
         
	    carry_object(MISC_D("cloth"))->wear();  
		carry_object(BINGQI_D("feizhen"))->wield();
		
		//carry_object("/d/hmy/npc/obj/heixuezhen")->wield(); 
}

void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
        ob->query_skill("tianmo-shou",1) < 350)
	 {
        command("say �����������书��������죬�ٻ�ȥ�����ɡ�");
        return;
     }
     if (ob->query_skill("poison",1)<100)
     {
		 command("say ��һ�㶾�ƶ���������Ȼ�����������������ʦ���ȰѶ���ѧ��120��˵��\n");
		 return;
     }
     command("say �ã��������б�����Ƚ��������������㻹��������������ˡ�");
     command("recruit " + ob->query("id"));
     ob->set("title","������̹�����ʹ��������");
}

int ask_zhen() 
{
  object me=this_player();
  object hxzhen;
  hxzhen=new("/d/hmy/npc/obj/heixuezhen");
  if (me->query("family/family_name")!="�������")
     return notify_fail("�㲻������̵��ӣ������������ʲô��");
  if (objectp(present("heixue shenzhen",me)))
     return notify_fail("�����ϲ��Ǵ�������ô��");
  if (me->query_skill("throwing",1)<350
	  ||me->query_skill("tianmo-shou",1)<350
	  ||me->query_skill("hand",1)<350
	  ||me->query_skill("mantian-huayu",1)<350||me->query_skill("force",1)<350)
     return notify_fail("���ַ���������������������õ��˺�Ѫ���������");
 
  if ((int)query("hxshenzhen")>0)
  { 
	  command("say ��Ѫ�����������������������ҪС��ʹ��Ϊ��,�������ܽ���ͬ��Χ����\n");
	  command("say ����һ�����룬���պ���\n");
	  hxzhen->move(me);
	  tell_object(me,HIC"����ݸ���һ����Ѫ���롣\n");
      add("hxshenzhen",-1);
	  return 1;
  }
  else {
	  command("say ����ͷֻ��һ�����룬�Ѿ����������ˡ����������\n");
	  return 0;

  }

}



string ask_huayu()
{
     object me=this_player();
     if (me->query("family/family_name")!="�������")
		return "�㲢������̵ĵ��ӣ��������������\n";
     if (time()-me->query("quest/hmy/mthy/huayu/time")<86400)
		return "������Ҳ̫�ڿ��ˡ�\n";

	 if (me->query_skill("mantian-huayu",1)<350
		 //||me->query_skill("hand",1)<350
		 //||me->query_skill("tianmo-shou",1)<350
		 ||me->query_skill("throwing",1)<350)
	    return "������컨�������似����350���޷�������˵��������ϣ���ȥ����Ŭ����\n";
	 if (me->query("quest/hmy/mthy/huayu/pass"))
		return "���Ѿ��⿪������⣬���˷�ɶʱ�䣿\n";
	 command("say ���컨�갵���ַ��������Ҷ�����ĵã�����ʹ�õĺá�һ�е��˶�����������֮�¡�\n");
	 command("say ������Ϻ�Ѫ���룬��������һ��¥��\n");
	 command("whisper "+me->query("id")+" �������ӵģ��������ˡ���������\n");
	 if (random(8)==5&&me->query("kar")>20) {
		
        command("chat* laugh "+me->query("id"));
        command("say ������������������ӣ��Ҵ��������������һ��������֡�\n");
		command("congra "+me->query("id"));
	
		log_file("quest/mthyhuayu",sprintf("%s(%s) �������ϵ�ָ�㣬�ɹ��������컨���������Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/huayu/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/mthy/huayu/pass","pass");	  	   
		return "��ϲ��⿪���컨�����ܣ�\n";
      }
	  else {
       
		log_file("quest/mthyhuayu",sprintf("%s(%s) �������컨�����ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/huayu/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/mthy/huayu/fail",1);
		me->set("quest/hmy/mthy/huayu/time",time());
		return "�������컨�����ʧ��!\n";

	  }

}
string ask_book()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/throwing-book.c");
	if (me->query("family/family_name") !="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�������϶��ô��\n");
		return "�������������Ĳ��Ű���";
	}
	if (me->query("generation")>10)
	{
		command("say ��ı���̫���ˣ��ӽ�Ŭ����\n");
		command("pat "+me->query("id"));
		return "���ǲ�������ӣ�\n";
	}
	if (query("book_count")<0)
	{
		command("say �����ؼ��Ѿ�Ϊ���е��������ˣ����������!\n");
		return "�ٺ٣��ܶ��˲�֪���Ҵ����°����������������Ǻ�Ѫ������ǽ���֮����\n";
	}
	book->move(me);
	add("book_count",-1);
	message_vision(HIY"$N�ݸ�$nһ���ؼ���\n"NOR,this_object(),me);
	return "������Ҫ�õ��ַ���������Խ��Խ�����׵ģ�\n";
}

string ask_tmsbook()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/hand-book.c");
	if (me->query("family/family_name") !="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�������϶��ô��\n");
		return "�������������Ĳ��Ű���";
	}
	if (me->query("generation")>10)
	{
		command("say ��ı���̫���ˣ��ӽ�Ŭ����\n");
		command("pat "+me->query("id"));
		return "���ǲ�������ӣ�\n";
	}
	if (query("tmsbook_count")<1)
	{
		command("say �ַ��ؼ��Ѿ�Ϊ���е��������ˣ����������!\n");
		return "�ٺ٣��ܶ��˲�֪���Ҵ��������컨�갵������������������ħ��Ҳ����һ�ž����ˣ�\n";
	}
	book->move(me);
	add("tmsbook_count",-1);
	message_vision(HIY"$N�ݸ�$nһ���ؼ���\n"NOR,this_object(),me);
	return "��ħ����ϰ�����һ�Ų���ľ�������Խ��Խ�����׵ģ�\n";
}