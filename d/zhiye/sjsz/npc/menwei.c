
inherit NPC;

void create()
{
        set_name("����", ({ "men wei", "menwei"}) );
        set("gender", "����" );
        set("age", 26);
        set("unique", 1);        
        set("long", "��λһ��������Ц��������\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("per", 30);
        set("chat_chance", 25);
        set("chat_msg", ({
"����˵������û���Խ�����ɽ���ɽׯ����\n",
        }) );
        setup();
        carry_object(ARMOR_D("skirt1.c"))->wear();
}

int accept_object(object who, object ob)
{
        
        if (ob->query("id")=="shijian ling" && ob->query("id")) 
        {
                tell_object(who, "������ͷ˵���������ɽׯ�ɣ���\n");
                who->set_temp("get_in_sjsz",1);
                return 1;
        }
		else
		{
			tell_object(who, "����һ��ü˵���������Ǻ����\n");			
		}
        return 0;
}
