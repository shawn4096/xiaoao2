// ��ѩͤ
#include <ansi.h>
inherit F_MASTER;
inherit NPC;
void create()
{
        set_name("��ѩͤ", ({ "xu xueting","xu" }));
	set("long", "����ʮ������ͣ�������������������ʹ��\n");
      set("gender", "����");
	set("title", "����������������ʹ");	
      set("age", 42);       
	set("str", 20);
      set("int", 22);
      set("con", 22);
      set("dex", 22);
      set("per", 15);
      set("combat_exp", 9800000);
      set("shen", -50000);
      set("attitude", "peaceful");
	set("max_qi",23500);
      set("max_jing",5000);
      set("neili",23000);
      set("max_neili",23000);
      set("jingli",5000);
      set("eff_jingli",5000);
	set("jiali",180);
	set("score", 20000);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry",450);
	set_skill("strike",450);
	set_skill("throwing",450);
	set_skill("huagu-mianzhang", 450);
	set_skill("youlong-shenfa",450);
	set_skill("dulong-dafa",450);
	set_skill("hansha-sheying",450);
	set_skill("poison",150);
	set_skill("shenlong-yaoli",200);
    set_skill("leg", 450);

	set_skill("shenlong-tuifa", 450);
	
	map_skill("leg", "shenlong-tuifa");
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("strike", "huagu-mianzhang");
	map_skill("parry","huagu-mianzhang");
	map_skill("throwing","hansha-sheying");
	prepare_skill("strike", "huagu-mianzhang");
    
	set("inquiry", ([
            "������" : "����������������������ң���ڡ�\n",
      //      "���ƶ�ҩ" : (: ask_liandu :),
			//"ѵ������" : (: ask_xunshe :),
		//	"����" : (: ask_fangqi :),
        ]));	
	
	create_family("������",2, "����ʹ");
	setup();
	carry_object("/d/sld/npc/obj/gcp")->wear();
}

void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
 	if(!myfam || myfam["family_name"] != "������")
           command("say ��Ǳ��̵��ӣ�������ȥ�����ʹ��̰�.");
       else if(ob->query("shen",1) > -200000)
           command("say �㻹�����ĺ���������ȥ��ɱ�����׵����˰�");
       else if(ob->query_skill("dulong-dafa",1)<200 )
	   {
			command("say �����󷨲���200���������Ʋ���200���������ҡ�");
            command("shake "+ob->query("id"));
	   }
       else
            {
           command("say �ðɣ��Ҿ����������ҵĵ��ӡ�");
	    command("recruit " + ob->query("id"));
       }
	return;	
}

int recognize_apprentice(object ob)
{
    mapping myfam;
    object hw;

    myfam = (mapping)ob->query("family");
if(!myfam || (myfam["family_name"] != "������")) return 0;
        if(!ob->is_apprentice_of(this_object())) return 0;
    if(myfam && (myfam["family_name"] == "������")&&(ob->query("shen",1) >0))
    {
    	command("say �ߣ��㾹Ȼ�ҺͰ׵����˸���һ���ǲ��ǲ�����ˣ���ȥ���ݺú÷�ʡ��ʡ�ɣ�");
	if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
		hw=load_object("/d/sld/npc/obj/heiwu");
	ob->set("in_heiwu",time());
	ob->move(hw);        
        return 0;
    }
    return 1;
}
