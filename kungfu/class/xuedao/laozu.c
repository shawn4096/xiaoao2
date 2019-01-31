// laozu.c Ѫ������
// by iceland

#include <ansi.h>
#include "/d/suzhou/npc/lchj.h";
#include "laozu.h";
#include <job_mul.h>
#include <get_place.h>

inherit NPC;
inherit F_MASTER;

string ask_yaoshi();
string ask_pizhi();
string ask_zujixiake();
string ask_xgjz();
string ask_fail();
string ask_hxjue();
string ask_jingang();

string ask_xuedao();
string ask_zijindao();
string ask_diyun();
string ask_xuedaojj();
string ask_xuesha();

string *names = ({
"/d/xuedao/shandong1","/d/xuedao/shandong2","/d/xuedao/shandong3","/d/xuedao/hollow","/d/xuedao/huangxidong1",
"/d/xuedao/shandong31","/d/xuedao/shandong32","/d/xuedao/chucangshi","/d/xuedao/huangxidong2","/d/xuedao/huangxidong3",
"/d/xuedao/sroad9","/d/xuedao/wangyougu","/d/xuedao/shulin2","/d/xuedao/huangxidong4","/d/xuedao/kengdao1","/d/xuedao/kedao2",
"/d/xuedao/shulin1","/d/xuedao/shulin3","/d/xuedao/shulin4","/d/xuedao/kedao3","/d/xuedao/kedao4",
"/d/xuedao/sroad8","/d/xuedao/sraod7","/d/xuedao/sroad6","/d/xuedao/sroad5","/d/xuedao/lingwushi",
"/d/xuedao/sroad4","/d/xuedao/sraod3","/d/xuedao/sroad2","/d/xuedao/sroad1","/d/xuedao/midong",
"/d/xuedao/sroad9","/d/xuedao/nroad1","/d/xuedao/nroad2","/d/xuedao/nroad3","/d/xuedao/shitang",
"/d/xuedao/nroad4","/d/xuedao/nroad5","/d/xuedao/nroad6","/d/xuedao/nroad7","/d/xuedao/shufang"
});


void create()
{
	object weapon;
	set_name("Ѫ������", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
	set("long",@LONG
����ĸ��ݣ��������ݣ�һ˫�۾�����׺ݵĹ�â�����˲���ֱ�ӡ����ڽ���
���Բ��̺�ɫ�����ƣ���ƾһ��Ѫ�����Ĺ��򶷰�������ԭ�����ֺ��ܡ�
LONG
	);
	set("title", HIR "Ѫ��������" NOR);
	set("gender", "����");
	set("class", "huanxi");
	set("age", 65);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 35);
	set("int", 30);
	set("con", 35);
	set("dex", 35);
	set("max_qi", 32100);
	set("eff_jing", 9600);
	set("max_jing",9600);
	set("max_jingli",8600);
	set("eff_jingli", 8600);
	set("no_bark",1);
	set("book",1);

	set("neili", 32500);
	set("max_neili", 32500);
	set("jiali", 250);
	set("combat_exp", 12500000);
	set("score", 500000);
	set("unique", 1);
	set("quest/xd/xddf/huaxue/pass",1);
	set("quest/xd/xddf/pizhi/pass",1);
	set("quest/xd/xdj/xuedao/pass",1);
	set("quest/xd/jglts/jingang/pass",1);
	set("quest/xd/xddf/chilian/pass",1);

	set_skill("huanxi-chan", 200);
	set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuedao-daofa", 520);
	set_skill("dodge", 500);
	set_skill("xueying-dunxing", 500);
	set_skill("strike", 500);
	set_skill("hongsha-zhang", 500);
	set_skill("hand", 500);
	set_skill("lansha-shou", 500);
	set_skill("blade",520);
	set_skill("xuedao-jing",500);
	set_skill("parry", 500 );
	set_skill("jingang-liantishu", 500 );

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("hand", "lansha-shou");
	map_skill("parry", "jingang-liantishu");
	map_skill("strike", "hongsha-zhang");
	map_skill("blade", "xuedao-daofa");

	prepare_skill("hand","lansha-shou");
	prepare_skill("strike","hongsha-zhang");

	create_family("Ѫ����", 4, "����");
	set("class", "huanxi");
	set("inquiry", ([
		"Ҫ��" : (: ask_yaoshi :),
		"Ѫ��" : (: ask_xuedao :),
		"�Ͻ�" : (: ask_zijindao :),

		"�������" : (: ask_zujixiake :),
		"ѩ�ȼ�ս" : (: ask_xgjz :),
		"����ʧ��" : (: ask_fail :),
		"Ѫ��������" : (: ask_xuedaojj :),
		"Ѫɷ" : (: ask_xuesha :),

		"��Ѫ������" : (: ask_hxjue :),
		"�������������" : (: ask_jingang :),
		"����" : (: ask_diyun :),

	]));

	set("chat_chance", 2);
	set("chat_msg", ({
		"Ѫ������̧��ͷ��������˼�����������������Բ�ˣ�����ɽɱ���˼������ˡ���\n",
		"Ѫ������޺޵�˵����ʲôʱ��������ԭ�����ָ��췭�ظ�����\n",
		"Ѫ������ҧ���гݣ���¶�׹��˵�����´�����ն�ݳ�����һ�����Ҳ��������\n",
		"Ѫ���������������������ʹ��ˣ�������һ��Ҳ����������������Ϊ���⡣\n",
	}) );
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: exert_function, "xuedao" :),
		(: exert_function, "xuesha" :),
		(: perform_action, "blade.chuanxin" :),
		(: perform_action, "blade.liuxing" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.bafang" :),
		(: perform_action, "blade.huaxue" :),
		(: perform_action, "blade.pizhi" :),
		(: perform_action, "blade.jixue" :),

	}));

	setup();
	carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
	if (clonep()){
		weapon = unew("clone/weapon/blade/xuedao");
		if(!weapon)weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon->wield();
	}
	//add_money("gold",5);
}
//��ͽ
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "Ѫ����") {
               command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��ŵ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 200) {
                command("say ��ϲ���Ǹ����书֮��������200�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 350) {
                command("say ����������Ǹ����书֮��������350�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 350) {
                command("say Ѫ�����Ǹ����书֮��������350�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }
        if (!ob->query("quest/xd/dichuan")) {
                command("say ��û�еմ���ݣ��Ҳ������㡣");
                return;
        }
        if (ob->query("job_time/Ѫ�����")<2000) {
                command("say ������Ѫ����������в���2000�Σ��Ҳ�Ը�����㡣");
                return;
        }
		if ((int)ob->query("shen") > -2000000) {
			command("hmm");
			command("say ��Ѫ����������Զ���Щ��ν�Ľ��������ĸ�����������ӣ�");
			command("say �������ڵ��������������Ϊͽ�����»ᱻ�˳�Ц��");
			return;
		}

        command("say �ðɣ��Ժ���ͺú��̷��ү�Ұɡ�");
        command("chat �ӽ��Ժ�"+ob->query("name")+"���Ƿ�ү�ҵ��״����ӣ�˭Ҫ�Ǹ��۸��ҵĹ�ͽ�����ɱ�ַ�ү���ĺ�������\n");
		command("chat �������ľ����������е�Ѫ����!\n");
        command("recruit " + ob->query("id"));
        ob->set("title", HIR "Ѫ�������״�����" NOR);
		return ;

}
//����Ѫ��������ֽ������quest
string ask_yaoshi()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ������ô��\n";
	}
	if (me->query("quest/xd/xddf/pizhi/pass"))
	{
		me->set("title",HBRED"Ѫ����������"NOR);
		return "���Ѿ��⿪��������⣬����Ե�޹���������������\n";
	}
//��������׽��Ů����
	if (!me->query_temp("quest/xd/xddf/pizhi/start"))
	{
		return "��ƽʱҲ��Т��Т�������ң�������Ե�޹���������������\n";
	}
	if (time()-me->query("quest/xd/xddf/pizhi/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return "�Ҵ�Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ�����ҵմ������ܴ�����߼��书����\n";
	}
	if (me->query("int")<40)
	{
		//command("say ��");
		return "��ϰѪ��������Ҫ���Ǹ����ԣ������첻��40�����Ǻú�����ȥ�ɣ���\n";
	}
	command("say �����㱦��ʦ��˵����������������˲�����Ů");
	command("say �Ҳ�֪���������С椶�����С��Т�������ҵģ������Ļ���ο��\n");
	command("say ��Ȼ�������Т�ģ������Ҿ�ָ��ָ���㣡\n");
	command("say �����ҵ�����һ��������������һ������������\n");
	command("say �Ǹ��ط��������������õط���\n");
	command("say һ����ϰ��ֽ�������ڣ�һ������ϰ�����������ڣ�\n");
	command("say ��ֽ������Ҫ��ϰ������һ��ֽ��һ����ȥ��ֻ����һ��ֽ��Ϊ�ɹ���\n");
	command("say ����������Ҫ��ϰ������һ�鶹����һ����ȥ��ֻ������ֽƬһ����Ķ���Ƭ��Ϊ�ɹ���\n");
	command("say ������������Ѫ������ϰѪ�������Ĳ������ţ�\n");
	command("say ��ú���ϰ�����ɺ��������ң�\n");
	command("heng ");
	me->delete_temp("quest/xd/xddf/pizhi/start");
	me->set("quest/xd/xddf/pizhi/asklaozu",1);
	return "һ�����֣��������У�\n";
}
//�����������Ȼ��ȥѩ��������
string ask_jingang()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ������ô��\n";
	}
	if (me->query("quest/xd/jglts/jingang/pass"))
	{
		//me->set("title",HBRED"Ѫ����������"NOR);
		return "���Ѿ��⿪��������⣬����Ե�޹���������������\n";
	}

	if (time()-me->query("quest/xd/jglts/jingang/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return "�Ҵ�Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ�����ҵմ������ܴ�����߼��书����\n";
	}
	if (me->query_skill("xuedao-jing",1)<350)
	{
		//command("say ��");
		return "��ϰѪ��������350�����Ǻú�����ȥ�ɣ���\n";
	}
	command("say �����������������²���֮�أ���Ҫ��С������������ҽ��������������С�");
	command("say �����ȼ������Ĺ��Ͳ���\n");
	command("say ��ĿǰΪֹ���Ѿ�����ˣ�\n");
	
	command("say ��Ѫ������Ҫ200�Σ����Ѿ�����ˣ�"+me->query("job_time/Ѫ������")+"\n");
	
	if (me->query("job_time/Ѫ������")>200)
	{
		command("say �����������ͨ����\n");

	} else return "����Ŭ��ȥ���Ѫ������job,ֱ��200��Ϊֹ��\n";
	
	command("say ��������������800�Σ����ܼ���ɣ�"+me->query("job_time/Ѫ������")+"��\n");
	if (me->query("job_time/Ѫ������")>800)
	{
		command("say Ѫ����������ͨ����\n");

	}else {
		return "����Ŭ��ȥ���Ѫ������job,ֱ��800��Ϊֹ��\n";
		
	}

	
	command("say �������������Ҫ2000�Σ��ܼ���ɣ�"+me->query("job_time/Ѫ�����")+"��\n");
	if (me->query("job_time/Ѫ�����")>2000)
	{
		command("say Ѫ���������ͨ����\n");

	} else return "����Ŭ��ȥ���Ѫ���������job,ֱ��2000��Ϊֹ��\n";
		
	command("say ��ǧ��Ҫ��ס�ˣ���Щ���������Ҷ����������Ҳ�����濼�����һ�ַ�ʽ��\n");
	command("say �����ҷǳ����ģ������Ҵ�Ѫ������ĵ��ӡ�\n");
	command("say ��Ȼ�����Ŭ������������ҳ�����Ѫ���ţ��Ҿ͸�����������ܣ�\n");
	command("say �����书����Ҫ����ѩɽ�������ȥ������\n");
	command("say ��ѩ����ѩ��Ϻ����������һ��������Ȼ���Լ�ͷ��������ѩ�У���\n");
	command("say �ٸ�������Ѫ���Ŷ��������ķ�����ʹ������ʹ��������\n");
	command("say �������Ŷ��أ�������������죬��Ҳ���Ҵ�Ѫ���Ķ���֮����\n");
	command("say �����޳ɴ����񹦣��ͻ���·ǳ��õĵ��ӣ�\n");
	command("say δ������������\n");
	command("consider ");
	command("say ʲô�������������ﲻ��������С����ѣ�\n");

	me->set_temp("quest/xd/jglts/jingang/start",1);

	return "�������������ͽ�������˼��\n";
}
//��Ѫ��������Ȼ��ȥɽ���ܶ�ĥ��

string ask_hxjue()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ������ô��\n";
	}
	if (me->query("quest/xd/xddf/huaxue/pass"))
	{
		//me->set("title",HBRED"Ѫ����������"NOR);
		return "���Ѿ��⿪��������⣬����Ե�޹���������������\n";
	}

	if (time()-me->query("quest/xd/xddf/huaxue/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return "�Ҵ�Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ�����ҵմ������ܴ�����߼��书����\n";
	}
	if (me->query_skill("xuedao-daofa",1)<300)
	{
		//command("say ��");
		return "��ϰѪ����������300�����Ǻú�����ȥ�ɣ���\n";
	}
	command("say �⻯Ѫ���������²���֮�أ���Ҫ��С������������ҽ��������������С�");
	command("say �����ȼ������Ĺ��Ͳ���\n");
	command("say ��ĿǰΪֹ���Ѿ�����ˣ�\n");


	command("say ��Ѫ������������ܼ�"+me->query("job_time/Ѫ������")+"��\n");
	command("say ��Ѫ�����������ܼ�"+me->query("job_time/Ѫ������")+"��\n");
	command("say ��ǧ��Ҫ��ס�ˣ���Щ���������Ҷ����������Ҳ�����濼�����һ�ַ�ʽ��\n");
	command("say ������������������似�������ȡ�\n");

	command("say Ѫ�������л�Ѫ����Ҫ����Ҫ��ζ�Ե���Ѫ�Լ��õ��ļ��ɣ�\n");
	command("say ���ܶ�֮����������һЩ���£���ȥ�Ķ���Ѫĥ���������ܷ��������ž�����\n");
	command("heng ");
	me->set_temp("quest/xd/xddf/huaxue/asklaozu",1);
	return "��Ѫ���Ե���ѪҲ��һ���漼��\n";
}

string ask_zujixiake()
{
	object ob, me;
	object daxia;
	object objwhere;
	//mixed str;
	string str,pos;
	int i,j;
	me=this_player();
	ob = this_object();
	
   
	if(me->query("family/family_name")!="Ѫ����") 
           return "�㲻����Ѫ���ŵ��ӣ��������ɶ�Թ��Ͳ�Ҫ�����ˡ� ";

//	if (me->query_temp("xd/xdzj"))
//		return "�Ҳ�������ȥ׷ɱһ��͵ѧ��Ѫ�����似�Ĵ�����ô����\n";

	if ((int)me->query("combat_exp") < 2000000)
		return "���书δ�ɲ���2m����ôΣ�յ������Ǳ����ˣ�\n";

	if (me->query("job_name") == "Ѫ�����")
		return "�������Ѫ������������Լ�ȥ��ϰ�书ȥ�ɣ�";

	if(me->query_condition("job_busy"))
		return "��������æ�������������أ�";
	if(me->query_condition("xdzj_job"))
		return "��������æ����Ѫ�����������Ϯ�������أ�";

	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";
    
	//�������λ������
    daxia=new("/d/xuedao/npc/robber");
	daxia->set("long",daxia->query("long")+"\n����"+me->query("name")+"����������Ϸ��Ĵ�����������Ԯ����\n"NOR);
	//daxia->set("owner",me->query("id"));
	//daxie->set("target",me->query("id"));
	
	daxia->set_temp("target", me->query("id") );
	//����i���Ѷ�ϵ��
	if (me->query("combat_exp")<2000000)
	{
		i=1+random(5);
	}
	else if (me->query("combat_exp")<9600000)
	{
		i=1+random(8);
	}
	else if (me->query("combat_exp")<12600000)
	{
		i=1+random(11);
	}
	else i=1+random(11);
	
	//��ֵ��������
	daxia->setparty(i,me->query("max_pot")-100,me->query("combat_exp"));
	daxia->apply_condition("npcdie_job",30);
	
	//����ӽ�ȥ״̬
	daxia->copy_player(me);//�ȳ�ʼ��npc��Ѫ���������һ�»���	
	pos=names[random(sizeof(names))];
	if (pos=="") 
	{
		pos=names[1];
	}
	if (!objectp(objwhere=find_object(pos)))
	{
		objwhere=load_object(pos);
	}
//	objwhere = names[random(sizeof(names))];
   // str = objwhere->query("short");

//	if (!objwhere) objwhere=names[1];//�����ֵ

	/*	
	for (j=0;j<sizeof(names);j++ )
		{
			objwhere=names[random(sizeof(names))];
			if (objwhere) break; 
			
		}*/
//	str=objwhere->query("short");
	
	message_vision(HIY"$N���ֱ�ȭ����Ѫ������˵���������棬������ս����\n"NOR,me);
 
	command("nod "+me->query("id"));
	command("say ������Բ�ˣ�����ɽɱ���˼������ˡ�\n");
	command("say �ߣ����ϸ���������������½�����Ҵ�Ѫ���ɵ���������ɷ�չ׳��\n");
	command("say �մ���ȥ�����ɵ�����ͷ�չ��������⣡\n");
	
	command("say ������ȥ��ɱ���ǵ���ͷ�ųơ��仨��ˮ�����Ĵ����ţ�\n");
	
	command("say �������ľ����Ұ���ЩϺ��з����������ʰ�ˣ�\n");
	
  //  if(!objwhere) objwhere = names[random(sizeof(names))];                
    //str = objwhere->query("short");
	if(!objwhere) objwhere =load_object("d/xuedao/wangyougu"); 

	command("say �յõ����е�����Ϣ����Ѫ����"+objwhere->query("short")+"һ������һ�������������������ν����������\n");
	command("say ���Ѿ��������ˣ��������������ֽС�"HIY+daxia->query("name")+"("+daxia->query("id")+NOR")�����ɱ����������ˣ�\n");

	command("say ������������ϲ���ɵľ�����Щ�������е�ֱ��ɱ�ˣ�����ͷ�������ң�Ů����֪������ô����\n");
	
	command("say �ߣ�\n");
	
	me->set_temp("xd/xdzj/place",objwhere->query("short"));
	me->set_temp("xd/xdzj/id",daxia->query("id"));
	me->set_temp("xd/xdzj/name",daxia->query("name"));
	me->set_temp("xd/xdzj/time",time());
	me->set_temp("xd/xdzj_job",1);
	daxia->move(objwhere);
	me->apply_condition("xdzj_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	

	
	return "�ߺߡ�����\n";
	
}

string ask_xgjz()
{
	object ob, me,obj;
	me=this_player();
	ob = this_object();
	
   
	if(me->query("family/family_name")!="Ѫ����") 
           return "�㲻����Ѫ���ŵ��ӣ��������ɶ�Թ��Ͳ�Ҫ�����ˡ� ";

	if (me->query_temp("xd/xgjz_job"))
		return "�Ҳ�������ȥ׷ɱ�Ĵ�����ô������\n";

	if ((int)me->query_skill("xuedao-daofa",1) < 500)
		return "��Ѫ�������书δ�ɣ�����500������ôΣ�յ������Ǳ����ˣ�\n";
	if ((int)me->query_skill("xuedao-jing",1) < 500)
		return "��Ѫ�����书δ�ɲ���500������ôΣ�յ������Ǳ����ˣ�\n";

	if (me->query("job_name") == "ѩ�ȼ�ս")
		return "�������ѩ�ȼ�ս�������Լ�ȥ��ϰ�书ȥ�ɣ�";

	if(me->query_condition("job_busy"))
		return "��������æ�������������أ�";
	if(me->query_condition("xgjz_busy"))
		return "��������æ����Ѫ��ѩ�ȼ�ս�������أ�";

	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";
    

	
 
	command("pat "+me->query("id"));
	
	command("say ��Ȼ�������Т�ģ�������ȥ��ɱ���ǵ���ͷ�ųơ��仨��ˮ�����Ĵ����ţ�\n");

	command("say ���Ĵ��������������еĸ��֣�����ѩ��һ����û��\n");
	command("say ���Ķ���ս�Ƚ����գ�����þ����޳ɽ�����������ܰ�Ȼ����������Բ�С�ľͻ������\n");
	
	command("say �ߣ���ѩ�����Ѿ�̽�����ף��ܹ���Ϊ�Ĳ㣡ÿһ�㶼��Ψһ������ͨ��\n");
	command("say �㵽�Ķ���Ҫ��ϸ�۲���Σ������������Ķ�����������Ӧ�����ҵ�����ͨ��(move up/down)��\n");
	command("say ��ͬһ���п���ͨ��(move east,west,north,south)��ǰ�������ƶ���\n");
	command("say ��Ϊ��ѩ�п��������ˣ�����ÿ�ƶ�һ�ζ�Ҫ��ϸ����(ting)���˵Ķ���\n");
	command("say �мǲ�Ҫ���Ǵ���һ���ط����Է�������͵Ϯ��\n");
	command("say ÿһ��ֻ��һ�����ˣ�ɱ�����Լ�������ɱȥȫ��ɱ�꣬Ҳ����ɱһ������ǧ��Ҫ��ǿ��\n");
	command("say �Ĵ����űȽ��ײУ���һ��ҪС�ġ�\n");

	me->set_temp("xd/xgjz_job",1);
	me->apply_condition("xgjz_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	if (objectp(obj=present("pi nang",me)))
	{
		destruct(obj);
	}
	obj=new("d/xuedao/obj/pinang");
	obj->set("owner",me->query("id"));
	obj->move(me);
	command("say �Ҹ���һ��Ƥ�ң����ɱ������ͷ��װ�����Ƥ���У������������ң�\n");
	
	
	return "�ߺߣ���Ȼ�����Գơ��仨��ˮ�����Ǿ�ɱ���Ǹ��仨��ˮ����\n";
	
}

int accept_object(object who,object obj)
{
	object obb;
	int exp,pot,exprelife,expdb,exp1;
	string msg;
	int i,j,jobs; 
	
	if (obj->query("kill_by"))
	{
		obb=obj->query("kill_by");
	}
	if (who->query_temp("xuegu/lutianshu")
		||who->query_temp("xuegu/huatiegan")
		||who->query_temp("xuegu/liuchengfeng")
		||who->query_temp("xuegu/shuidai"))
	{
		exp=0;
		pot=0;
		exp1=0;
		jobs=who->query("job_time/ѩ�ȼ�ս");
		//jobs=jobs%50;
		//ѩ�ȼ�սΪ50�ı���
	}	
	else if (who->query_temp("xd/xdzj"))
	{
		exp=100+random(20);
		pot=50+random(10);
		jobs=who->query("job_time/Ѫ�����");
		//jobs=jobs%10;
		//Ѫ������Ϊ10�ı���
	}

	exprelife=0;
	expdb=0;   
	
//�����ݲ�ͬ������ͬ
	if(!who) return 0;
	

	i=random(who->query("kar"));
	j=20;

	if(who->query("buyvip") )
	{
       exp = exp + exp* 20/ 100;
	   j=18;
	}
	else if(who->query("y-card-vip"))
	{
       exp = exp + exp * 10 / 100;
	    j=15;
	}
	else if(who->query("m-card-vip"))
	{
       exp = exp + exp * 5 / 100;
	    j=10;
	}
	j=random(j);
	
	if (obb
		&& obj->query("name")==who->query_temp("xd/xdzj/name")+"���׼�"
		&& obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"�����������ɱ�ˣ��Һܸ��ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		command("say ������ȥ�ú���Ϣ�ɣ�\n");
		destruct(obj);

		message_vision(RED"\n\nѪ������˦�ֽ������ͷ����Զ��������ѩ��֮�У�\n"NOR,who);
	
	//���ý���ϵͳ
	  TASKREWARD_D->get_reward(who,"Ѫ�����",-1,0,0,5+j,0,0,0,"Ѫ������");  
	
	/*	
		msg=YEL"Ѫ�������ͷ���������Ĵָ�����ָ�����"+exp+"�㾭��ֵ��"+pot+"��Ǳ�ܣ�\n"NOR;
		//����exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"��������ڼ䣬���ֶ�����"+chinese_number(exprelife)+"�㾭��ֵ��\n"NOR;

        }

        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "˫�����齱���ڼ䣬�����صõ���" + HIW + chinese_number(expdb) + HIC + "��" + HIM + "���飡\n"NOR;
        }		
		//����
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(who,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
        }
	//����
	*/
		//who->add("combat_exp",exp);
		//who->add("potential",pot);
		
		who->add("job_time/Ѫ�����",1);
		who->set("job_name","Ѫ�����");
		//message_vision(msg,who);
		//tell_object(who,msg);
	//Ѫ���������ͷ��
		jobs=who->query("job_time/Ѫ�����");
		if (wizardp(who))
			write("jobs="+jobs);
		if (random(who->query("job_time/Ѫ�����"))>4000
			&& i > 24
			&& j < 4
			&& !who->query("quest/xd/xddf/chilian/pass")
			&& jobs % 40==0)
		{
			message_vision(HIG"\nѪ�������$N������Ц��˵��������������޲��������Һ�ϲ������\n"NOR,who,this_object());
			command("pat "+who->query("id"));
			command("say ��Ȼ�����Ŭ���������Ҿͽ���Ѫ�������г����񵶾������ڸ��㣬�����ã�\n");
			command("whisper "+who->query("id"));
			message_vision(HBRED"\n$nʹ��Ѫ������֮���衸�������Ρ�����������$n����ʳָ��Ѫ����һ����������������ӳ��ֱϮ$N��ȫ���Ѩ��\n"NOR, who,this_object());
			message_vision(HIC"\n$N��ʱ�ŵð��������⵶������$N���еı��������ʮ�أ�\n"NOR, who,this_object());
			message_vision(HIG"\n$N��������Ѫ������������$n���ָⷬ�������Դ��ڣ���ʱ����!\n"NOR, who,this_object());
			
			message_vision(HBYEL+HIW"��ϲ�����������Ŭ���Ĺ������ڻ��������ͬ����ѧ�ó����񵶾�����\n��\n"NOR,who);
			command("chat ��ϲ"+who->query("name")+"��Ϊ��Ѫ��������һ���֣���ʵս���޳ɳ����񵶾���!\n");
			log_file("quest/xddfchilian", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��Ѫ�������г����񵶾���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				who->name(1),who->query("id"), who->query("quest/dls/hyd/fail"),i,j,who->query("kar"),who->query("combat_exp")) );
	

			who->set("quest/xd/xddf/chilian/pass",1);
		}
		who->apply_condition("job_busy",2);
		who->apply_condition("xdzj_job",2);
		who->delete_temp("xd/xdzj");
		return 1;	
	}

	
	
//ѩ�ȼ�ս����ͷ
	if (objectp(obb=obj->query("kill_by"))
		&&who->query_temp("xuegu")
		&&(obj->query("name")=="½������׼�"||obj->query("name")=="�����ɵ��׼�"||obj->query("name")=="���з���׼�"||obj->query("name")=="ˮ᷵��׼�")
		&& obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"�����ν�����Ÿ���ɱ�ˣ��Һܸ��ˣ�\n");
		command("say ������ϲ���ɵľ����������ţ�\n");

		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		command("say ������ȥ�ú���Ϣ�ɣ�\n");
		switch (obj->query("name"))
		{
			case "½������׼�":
				if (!who->query_temp("xuegu/lutianshu")) break;				
				exp=200+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/lutianshu");
				break;
			case "�����ɵ��׼�":
				if (!who->query_temp("xuegu/huatiegan")) break;
				exp=250+random(100);
				pot=exp/20;
				exp1=random(10)+10;
				who->delete_temp("xuegu/huatiegan");
				break;
			case "���з���׼�":
				if (!who->query_temp("xuegu/liuchengfeng")) break;
				exp=300+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/liuchengfeng");
				break;
			case "ˮ᷵��׼�":
				if (!who->query_temp("xuegu/shuidai")) break;
				exp=350+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/shuidai");
				break;
			
		}

		if(who->query("buyvip") )		
			exp = exp + exp* 20/ 100;
		else if(who->query("y-card-vip"))
		    exp = exp + exp * 10 / 100;
		else if(who->query("m-card-vip"))	
			exp = exp + exp * 5 / 100;


		message_vision(RED"\n\nѪ������˦�ֽ�"+obj->query("name")+"����Զ��������ѩ��֮�У�\n"NOR,who);
		destruct(obj);

		/*
		msg=YEL"Ѫ�������ͷ���������Ĵָ�����ָ�����"+exp+"�㾭��ֵ��"+pot+"��Ǳ�ܣ�\n"NOR;
		//����exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"��������ڼ䣬���ֶ�����"+chinese_number(exprelife)+"�㾭��ֵ��\n"NOR;

        }
		//˫�����齱��
        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "˫�����齱���ڼ䣬�����صõ���" + HIW + chinese_number(expdb) + HIC + "��" + HIM + "���飡\n"NOR;
        }		
		//����
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(who,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
        }
		*/
	//����
		//who->add("combat_exp",exp);
		//who->add("potential",pot);
		TASKREWARD_D->get_reward(who,"ѩ�ȼ�ս",-1,0,0,exp1,0,0,0,"Ѫ������");  
		
		who->add("job_time/ѩ�ȼ�ս",1);
		who->set("job_name","ѩ�ȼ�ս");
		//message_vision(msg,who);
		//tell_object(who,msg);
//Ѫ���������ͷ��
		if (random(who->query("job_time/ѩ�ȼ�ս"))>4000
			&& i > 20
			&& random(j)<5
			&& random(10)==3
			&& jobs%50==0)
		{
			message_vision(HIG"\nѪ��������������Ц��˵��������������޲��������Һ�ϲ������\n"NOR,who);
			command("pat "+who->query("id"));
			command("say ��Ȼ�����Ŭ���������Ҿͽ���Ѫ������������书�ؼ���Ѫ���ؼ����������ڸ��㣬�����ã�\n");
			command("whisper "+who->query("id"));
			message_vision(HBRED"\n$nʹ��Ѫ������֮���衸Ѫ���󷨡�����������$nѪ����ʩչ�󣬻�����Ѫ��ӿ��\n"NOR, who,this_object());
			message_vision(HIC"\n$n��$N˵������������Ժ�ÿ�춼������ҹ���Ѫ���󷨵������ˡ���\n"NOR, who,this_object());
			
			message_vision(HBYEL+HIW"��ϲ�����������Ŭ���Ĺ������ڻ��������ͬ�����ѧϰ��Ѫ���ؼ����Ļ��ᣡ\n��\n"NOR,who);
			who->set("quest/xd/xdj/xuedao/start",1);
			log_file("quest/xdjxuedao", sprintf("%8s(%8s) �õ�ѧϰѪ�����ؼ��ĵĻ��ᡣ�����iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				who->name(1),who->query("id"), who->query("quest/xd/xdj/xuedao/fail"),i,j,who->query("kar"),who->query("combat_exp")) );
		}
		who->apply_condition("job_busy",2);
		who->apply_condition("xgjz_job",2);
		who->delete_temp("xd/xgjz");
		who->delete_temp("xd/xgjz_job");
		return 1;
	}

	
} 
int ask_fail()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));

	if (me->query_temp("xd/xdzj"))
	{
		command("say ��Ȼ���겻��������͵��������ʱ��ȥЪϢȥ�ˣ���ֱ���Ƿ����\n");
		me->apply_condition("job_busy",15);
		me->delete_temp("xd/xdzj");
		return 1;
	}
	if (me->query_temp("xd/xgjz")
		||me->query_temp("xd/xgjz_job")
		||me->query_temp("xuegu"))
	{
		command("say ��Ȼ���겻�ɡ�ѩ�ȼ�ս�����������ʱ��ȥЪϢȥ�ˣ���ֱ���Ƿ����\n");
		me->apply_condition("job_busy",15);
		me->delete_temp("xd");
		me->delete_temp("xuegu");
	//	me->delete_temp("xd/xdzj");
		return 1;
	}

	command("say ��ʲô��û����Ϲ����ʲô��\n");
	
	me->delete_temp("xd");

	//me->apply_condtion("job_busy",4);

	return 1;
}

void die()
{
	object ob,room;
	ob=this_object();
	room=load_object("d/xueshan/xuegu");

	if (!query_temp("living"))
	{
		ob = new("/kungfu/class/xuedao/laozu");
		ob->move("/d/xueshan/xuegu");
	}
	::die();
}

