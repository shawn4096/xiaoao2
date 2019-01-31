// Room: /d/wizard/yabi.c
#include <ansi.h>
inherit ROOM; //�̳� ROOM ��

string qipan();
void create() // ��������;�����涨���������
{
	set("short", HIB"�±�ǰ"NOR); // ����� ������
	set("long","·���˴����ѶϾ������͵��±��ϲ�֪��˭�Դ���ͨ��̳���γ֮���γ�\n"
		"һ������(qipan)�����������������ӣ������������["HIC"��"HIG"��"HIY"���"NOR"]����˵�⿪��\n"
		"����߱��д��Ե�������Ϻܶ���ֶ�����һ�ԣ��������ܽ⿪�˾֡�\n"
		);// ����ĳ�����
	set("exits", ([ "east" : __DIR__"shangu",])); // ��ͬ�ķ���ָ��,��ת��
	//set("valid_startroom", 1);//ʹ�÷�����Գ�Ϊ��һ�ν����ĵط�
	set("outdoors","xiaoyao");
	set("no_fight",1);
	set("no_get",1);
	set("item_desc", (["qipan" : (: qipan :),]));


	set("objects", (["/d/xiaoyao/npc/suxinghe" : 1 ]) );
	
	setup(); //���ù���,�ճ�����
}
string qipan()
{	
	object me=this_player();
	if (me->query("quest/�����˲�/��ڤ��/look")<1 && me->query("quest/�����˲�/��ڤ��/step1")<1)
	{
		return "["HIC"��"HIG"��"HIY"���"NOR"]\n";
	}
	if (me->query("quest/�����˲�/��ڤ��/look")>0 && me->query("quest/�����˲�/��ڤ��/step1")<1)
	{
		me->start_busy(180);
		call_out("qipan1", 3,this_player());
	}
	if (me->query("quest/�����˲�/��ڤ��/step1")>0)
	{
		return "��ϲ��["HIC"��"HIG"��"HIY"���"NOR"]�ѱ����ƽ��ˡ�\n";
	}
}

void qipan1(object me)
{
		message("vision","\n�㶢��������ϸ���꣬��ǰ����ȴ����ģ����������\n", this_object());
		remove_call_out("qipan2");
		call_out("qipan2", 3,me);
}
void qipan2(object me)
{
	message("vision",HIG"\n\n����ϵİ��Ӻ����ƺ��������˽���ʿ�䣬��һ��������һ����Ӫ����Χס�ң���Χס�㣬\n"
		"��������������ɱ������������������������׼׵ı�������ڼ׵ĵ���Χס�ˣ������\n"
		"ͻ��ʼ��ɱ������Χ������Խ��Խ�ǽ�����\n"NOR, this_object());

			remove_call_out("qipan3");
			call_out("qipan3", 3,me);
}

void qipan3(object me)
{

	message("vision",HIY"\n\n�·����������书��������������������ɱ��ȭ�Ʒ��ɣ���ȥ������ս��һ�š�������۲�˫\n"
		"����������ƽ������ѧ���Щ����͸�ĵط������������򣬵���ϸ��˼ȴ�ֲ�����⡣��\n"
		"ֻ��ȫ�������·�ʧȥ�˿�����Ѫ���������Ҵܣ����ɵ���Ϣ����������\n"NOR, this_object());
	if(me->query("quest/�����˲�/��ڤ��/temp")<1)	//�˴��⿪�����Ժ�� ����Ϊ������� �� call me->set(quest/�����˲�/��ڤ��/temp,1����0)������ 0����ʧ�� 1����ɹ�
	{
		me->start_busy(-1);
		me->unconcious();//�ε���ʧ�ܡ�
		me->set("quest/�����˲�/��ڤ��/step1",0);
		me->set("quest/�����˲�/��ڤ��/fail",1);
	}
	else
	{
		message("vision",HIW"\n\n��ͻȻ�����������������߶�ʮһ�������Ա߰�ɫ���ӣ�һ�ӵ����������롾"HIR"��Ԫλ"HIW"��������\n"
		"һ���£����ӱ�Ŀ���Ӷ�ɱ���Լ�һ������󣬾���ٳʿ��ʣ�������Ȼ��ռ���ƣ�����ȴ\n"
		"���л�������أ���������ǰ��㸿�ָ��ţ��˴�ʧ�ˡ�\n"NOR, this_object());
			remove_call_out("xiaqi1");
			call_out("xiaqi1", 3,me);

	}
}

void xiaqi1(object me)
{
	message("vision",CYN"\n\n\n���ǺӴ�Ц��������������һ�е���ѥ����\n"
		NOR"���ǺӶ�������ǧ���򻯣�ÿһ�Ŷ�������Ȼ���أ�����Ӧ��һ�ź��塣\n"NOR, this_object());
			remove_call_out("xiaqi2");
			call_out("xiaqi2", 3,me);

}
void xiaqi2(object me)
{
	message("vision",NOR"\n���Լ�˼���������Աߵİ��������ˡ�"HIM"��ȥ��λ�İ˰�·"NOR"����\n"NOR, this_object());
			remove_call_out("xiaqi3");
			call_out("xiaqi3", 3,me);
}

void xiaqi3(object me)
{
	message("vision",NOR"\n���Ǻ�΢΢һЦ��Ӧ��һ�ź��塣\n"
		CYN"���Ǻӵ�����������������ƽ��أ���\n"NOR, this_object());
			remove_call_out("xiaqi4");
			call_out("xiaqi4", 3,me);
}

void xiaqi4(object me)
{
	message("vision",NOR"\n�㡾"HIR"��Ԫλ"NOR"����ɱһƬ���Ӻ�����֮�����ƣ���·��Ȼ���ʡ�\n"
		"�漴���ڡ�"MAG"��ƽ��λ����·"NOR"��������һ�ӡ�\n"NOR, this_object());
			remove_call_out("xiaqi5");
			call_out("xiaqi5", 3,me);
}

void xiaqi5(object me)
{
	message("vision",NOR"\n�����˷��������Ѿ�ռ���Ϸ壬��������֮��Ǭ��Ťת�����Ǻ������Ц�����������ƺ��������ת��\n"
		CYN"���Ǻӵ������벻������ʦ�����µ������ʮ�����������ƽ⣬���յ���Ե֮���ԡ�"HIG"����ѥ"CYN"��֮���ƽ�˾֣���Ҳ����Ҳ����\n"
		HIR"\n\n\n���Ǻ�ͻȻת��������ץס����·���һ�Ž��������±ڣ�\n"
		HIB"��ֻ��һ�ɴ������β�����һײ��������������һ�������ǰֱ���˳�ȥ��\n"
		HIC"\n\n������һ�ţ����һ��������ɵı������۾������� ������\n\n"NOR, this_object());
		me->start_busy(-1);
		me->set("quest/�����˲�/��ڤ��/step1",1);//step1�ɹ���
		me->set("quest/�����˲�/��ڤ��/look",0);
		me->move(__DIR__"shandong");
}