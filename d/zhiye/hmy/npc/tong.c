// Finish by Numa@SJ 2000.8
// edit by sohu,add quest

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_tmd();
void create()
{
        set_name("ͯ����", ({ "tong baixiong", "tong", "baixiong"}));
        set("long", "һ���뷨��׵����ߣ���Ŀ��࣬˫Ŀ��������\n"+
        	"���ƹ������½̷����ã������Ž������ж��������\n");
        set("title",HIY"������� "HIC"��������"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 38);

        set("max_qi", 13500);
        set("max_jing", 2200);
        set("eff_jingli", 2200);
        set("jiali", 200);
        set("combat_exp", 4800000);
        set("shen", -1);

        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
        set_skill("blade", 450);
		set_skill("tianmo-jue", 200);
        set_skill("huanmo-wubu", 450);
        set_skill("tianmo-dao", 450);
        set_skill("tianmo-gong", 450);
        set_skill("strike", 450);
        set_skill("tianmo-zhang", 450);
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("blade", "tianmo-dao");
        map_skill("parry", "tianmo-dao");
        map_skill("strike", "tianmo-zhang");
        prepare_skill("strike", "tianmo-zhang");
        create_family("�������",8,"����");

        
        set("inquiry", ([
                 "��ħ����" : (: ask_tmd :),
		        // "��������" : (: ask_sword :),
        ]));
        
        setup();
		carry_object(BINGQI_D("blade"))->wield();
 
        carry_object(MISC_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") >-50000){
        command("say �㲻���ĺ����������ĵز������Ҳ����㣡");
        return;
        }
	 if(ob->query_skill("tianmo-gong",1)<250){
        command("say �����ħ��������������Ҫ����Ŭ����");
        return;
	 }
     if(ob->query_skill("tianmo-jue",1)<180){
        command("say �����ħ����������Ҫ����Ŭ����");
        return;
	 }
	 
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}

string ask_tmd()
{
     object me=this_player();
     if (me->query("family/family_name")!="�������")
		return "�㲢������̵ĵ��ӣ��������������\n";
     if (time()-me->query("quest/hmy/tmd/time")<86400)
		return "������Ҳ̫�ڿ��ˡ�\n";
	 if (me->query_skill("tianmo-dao",1)<250)
	    return "�����ħ���似����250���޷�������˵��������ϣ���ȥ����Ŭ����\n";
	 if (me->query("quest/hmy/tmd/pass"))
		return "���Ѿ��⿪������⣬���˷�ɶʱ�䣿\n";
	 command("say ��ħ����������ʹ�õ�С���ɣ������Ҷ�����ĵã�����ʹ�õĺ�\n");
	 command("say ��ħ����������������ǧ�򲻿�С�������ŵ��������������������ˣ�\n");
	 command("whisper "+me->query("id")+" �������ӵģ��������ˡ��ҵ����С��͡��쵶�ƵС�\n");

	 if (random(me->query("kar"))>27) {
		command("chat* laugh "+me->query("id"));
        command("say ������������������ӣ��Ҵ��������������һ��������֡�\n");
		command("congra "+me->query("id"));
		//command("say ��⿪");
		//message_vision(HIC"$N���ڽ⿪��ħ�������ܡ���\n"NOR,me);
		log_file("quest/tianmd",sprintf("%s(%s) ��ͯ���ܵ�ָ�㣬�ɹ�������ħ�����ؼ�����Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("tmd/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/tmd/pass",1);	  	   
		return "��ϲ��⿪��ħ�������ܣ�\n";
      }else {
        //message_vision(HIC"$N������ħ��������ʧ�ܣ�\n"NOR,me);
		log_file("quest/tianmd",sprintf("%s(%s) ������ħ�����ؼ�ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("tmd/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/tmd/fail",1);
		me->set("quest/hmy/tmd/time",time());
		return "������ħ������ʧ��!\n";

	  }

}


