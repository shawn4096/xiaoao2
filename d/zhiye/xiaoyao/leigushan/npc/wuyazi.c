// NPC: /d/wizard/npc/wuyazi.c
inherit NPC;
#include <skill.h> 
#include <ansi.h>
#include <command.h>

void create()
{
	set_name("������", ({ "wuyazi","wuya","zi" }));
    set("title", HBBLU"����ң�����š�"NOR);
	set("gender", "����" ); // �Ա�
        set("age", 40);
		set("per", 40);
        set("shen_type", 1);
	set("str", 50);
	set("int", 50);
	set("con", 50);
	set("dex", 50);
	set("max_qi", 62000);
	set("max_jing", 6000);
	set("eff_jingli", 9000);
	set("neili", 62000);
	set("max_neili", 62000);
	set("jiali", 250);
	set("combat_exp", 26400000);


			set_skill("force", 950);
			set_skill("beiming-shengong", 950);
			set_skill("dodge", 950);
			set_skill("parry", 950);
			set_skill("lingbo-weibu", 950);
			set_skill("hand", 950);
			set_skill("strike", 950);
			set_skill("zhemei-shou", 950);
			set_skill("liuyang-zhang", 950);
			map_skill("force","beiming-shengong");
			map_skill("dodge","lingbo-weibu");
			map_skill("parry","zhemei-shou");
			
			map_skill("hand","zhemei-shou");
			

			prepare_skill("hand", "zhemei-shou");
			prepare_skill("strike", "liuyang-zhang");			

        setup();
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(ARMOR_D("shoes"))->wear();


}

void init()
{
	object ob = this_player();
	add_action("do_ketou","ketou");


	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {

		if (ob->query("xiaoyao/zhenlong/pass"))
		{
		command("nod "+ob->query("id"));
		remove_call_out("chenggong");
	    call_out("chenggong", 3, ob);		
		}
		else
		{
		remove_call_out("shibai");
	    call_out("shibai", 3, ob);
		}
	}
}


void shibai(object ob)
{
	command("sigh");
	command("say ���ȥ�գ�");
	ob->move("/d/leigushan/yabiqian");
}

void chenggong(object ob)
{
	command("say ���ܽ����ҵ���֣��������ǣ����Ƿ�ͬС�ɣ�����ò��ˣ�ȴ�վ����У��ѣ��ѣ��ѣ������ѣ��ѣ��ѣ�");
	command("look "+ob->query("id"));
	command("say ����������ˣ�������۾����������ײ�Ľ�������ֽ⿪�������Ե��񣬻��ܰ��Ҵ��£���δ��֪���ã��ã��Ժ��ӣ�����¿�ͷ�գ�");
}

int do_ketou(string arg)
{
	object ob = this_player();
if ( ! arg ) return 0;
if ( arg == "wuyazi" )
{
	message_vision("$N�����Ĺ򵹣�˫ϥ���أ����������������ӿ��˾Ÿ���ͷ. \n", ob);
	remove_call_out("shoutu");
	call_out("shoutu", 0, ob);
	return 1;
}

}

void shoutu(object ob)
{
	
	 mapping skl = ob->query_skills();	
     string *sk;	
     int i;		
 	 sk = keys(skl);
     i = sizeof(sk);	 
	 
	 
	  while (i--) {
        if (		
		 sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong" || sk[i] == "bahuang-gong" 
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"||sk[i] == "baduan-jin" 
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong" || sk[i] == "dulong-dafa" || sk[i] == "hamagong"  || sk[i] == "xuedao-jing" ) 
		 {		   
		   ob->map_skill("force");
           ob->delete_skill(sk[i]);	//���������ڹ�	   
           message_vision(HIY"$Nֻ��ȫ��������أ���������һ�����ˮ֮��һ�㣬����ë��֮�У��ƺ���������ð����˵�������泩��\n"NOR,ob);	
           message_vision(HIY"�����ӷſ�$N����Ц�����������������ñ��š���ڤ�񹦡��������" + to_chinese(sk[i]) +"����ȥ����\n"NOR,ob);              
		  }
       continue; 		 	  
      }
	  
	  message_vision(HIY"�����ӹ���һЦ��ͻȻ���ΰ����ڰ����һ�����ͷ��������������ݽǣ�������������һ�ţ�ͷ�½��ϵĵ����������Դ�����$N��ͷ������������Ǻ���������\n"NOR,ob);	
	  ob->delete("family");
	  
	  //���ﲻҪ��ʦ��ѧ�գ���Ϊ�Ѿ���������ʦ���ˣ������书ͨ�����ܻ��
	   if (ob->query_skill("xixing-dafa")) {
		   command("say Ŷ�����ƺ�ѧ����ڤ�񹦵�Ƥë�����ǲ���������������м���Σ�����һ��ǰ��㻯ȥ�ɡ�");
		   ob->map_skill("force");
		   ob->delete_skill("xixing-dafa");
	   }
		   
	  if (ob->query_skill("beiming-shengong")) command("say Ŷ�����Ȼ�Ѿ�ѧ�ᡮ��ڤ�񹦡����ǵ�ʡ�²��١�");
	  else ob->set_skill("beiming-shengong",220);
	  ob->set_skill("liuyang-zhang",300);	  
	  ob->set_skill("zhemei-shou",300);
	  ob->set_skill("lingbo-weibu",300);
	  ob->set_skill("ruyi-dao",300);
	  ob->create_family("��ң��",2, "����");
	  ob->set("family/master_name","������");     
	//"��˵��֮�䣬����ֻ��ȫ��������أ���������һ�����ˮ֮��һ�㣬����ë��֮�У��ƺ���������ð����˵�������泩������Ƭ�̣������˷ſ�������Ц�����������������ñ��š���ڤ�񹦡��������������������ȥ������"
	//"���˹���һЦ��ͻȻ���ΰ����ڰ����һ�����ͷ��������������ݽǣ�������������һ�ţ�ͷ�½��ϵĵ����������Դ����������ͷ������������Ǻ���������"
	//"������һ��ͼ��������������������帣֮���������ڴ��������ɽ�У���Ѱ����������ѧ�伮�����ڣ�������ϰ"
	command("say �ã��ã��ҵĹ�ͽ���������ˡ���ڤ�񹦡����ѽ���ʮ�������Ϊ������ע�����������");
	command("say ������һ��ͼ��������������������帣֮���������ڴ��������ɽ�У���Ѱ����������ѧ�伮�����ڣ�������ϰ��");
	ob->set("title",HBBLU"������"NOR+HIY"���ŵ���"NOR);
	ob->set("mytitle/quest/zhenlong",HBBLU"������"NOR+HIY"���ŵ���"NOR);
	//ob->set("quest/�����˲�/��ڤ��/step2",1);

}
