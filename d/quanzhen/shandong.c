//By Jpei ����������
//���ú�ɽ�Ǳչس���
//�������˱չ�֮��
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "��ɽɽ��");
        set("long", @LONG
����������������ǰ���޵�ɽ��������Ӷ������������������
�߲�½�룬���������쳣���������ǿ��������ڱ���������һ����
���ϰڷ��˼������ؾ��䣬�񰸺󶴱���������һ����(hua)������
�����һ����������ּ���zi���������˳���Ⱦ���������ࡣ
LONG);
        set("exits", ([
                "out" : __DIR__"xiaolu3",
        ]));
        set("item_desc", ([
        	"hua": YEL "������һ�������ʿ�ı�Ӱ��������ʲô��"
                       "ò�����е���һ��ָ�Ŷ�������ּ���\n  �������š�" HIR "��"
                       "������" NOR + YEL "�������֡�\n" NOR,
			"zi": HIW "��д�ż�־������ġ�������ʦ������������ ԭ�������������죬̫
��׿�������ڣ���ʥϮ���������Դ����ȷ������ɣ��������
�󿪶����ա�������̣��������ˡ�Ȼ��˳����¡����ʱ���裬ȥʥ
��Զ����ⲻ���������ȵ�������������֦Ҷ�������׻�������ɢ��
��֮���ӣ�������֮���飬������Դ��������ɫ����Ϳ�յף������
��������ʥ�˸��𣬾���Ԫһ��֮����������£�Ӧ��������֮����
ͦ���ڶ������������潨�ڳж���ά��Ŧ��������ʵ������¼�ԡ���
�׶��¶����ظ����ɡ�������ʦ������Ҳ��������,����ϸ������ƪ�ּ�
�ƺ��е���˼����������ʲô���д���ȥ�о���yanjiu����\n" NOR,

        ]) );
        set("paper_count", 1);

        setup();
}

void init()
{
       if (this_player()->query("quest/qz/dichuan"))
	   {
		    add_action("do_ketou", "ketou");
			add_action("do_fan","fankan");
			add_action("do_canwu","canwu");
			
		}
		else {
			write(HIC"�𴦻���Զ����������ɽ����ʦ����֮��������Ҵ�ȫ��մ����ӣ���������������\n"NOR);
			return 0;
		}
			add_action("do_yanjiu","yanjiu");

}
int do_yanjiu(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/ketouok"))
	{
		return notify_fail("���������У����о��˰���ʲô��û��������\n");
	}
	if (arg!="zi")
	{
		return notify_fail("��Ҫ��Ħ�о�ʲô��\n");
	}
			//���ֽ������Ҫ����Ҫ
	if (random(me->query("kar"))>25)
	{
			message_vision(HIY"$N�����������˵���ʾ���������У��ӵ��ؾ����з���һ���������ּǣ������Ȼд�š������������Ҫ��\n"NOR,me);
			message_vision(HIY"$N��ʱ���´�ϲ����æ����Ҫ��׼������canwu����\n"NOR,me);
			me->set_temp("qz/findyusuo",1);
	}
	write("�������Ǳ����������ʮ�ľ������о�������\n");
	return 1;
}
//����������
int do_canwu(string arg)
{
		int i;
        object me;
		me= this_player();
		i=me->query_int(1);
		if (me->query_skill("jinguan-yusuojue",1)>600)
			i=i/8;
		else if (me->query_skill("jinguan-yusuojue",1)>550)
			i=i/6;
		else if (me->query_skill("jinguan-yusuojue",1)>500)
			i=i/4;
		else if (me->query_skill("jinguan-yusuojue",1)>450)
			i=i/3;
		else if (me->query_skill("jinguan-yusuojue",1)>400)
			i=i/2;
		else i=i;

		if (!arg)
		{
			return notify_fail("���ҷ�һͨ���ؾ��䣬һ������\n");
		}
		if (!me->query_temp("qz/findyusuo")) {
			me->start_busy(2);
			return notify_fail("����Ҳ���һ�������з��겻��\n");
		}
		if (me->query_skill("jinguan-yusuojue",1)<200)
		{
			return notify_fail("��Ľ������������200�����޷����˲����ķ���Ҫ��\n");
		}
		if (me->query_skill("xiantian-gong",1)<200)
		{
			return notify_fail("������칦����200�����޷����˲����ķ���Ҫ��\n");
		}
		if (me->query_skill("taoism",1)<200)
		{
			return notify_fail("��ĵ��¾�����200�����޷����˲����ķ���Ҫ��\n");
		}
		if (me->query_int()<30)
		{
			return notify_fail("������Բ���30���޷����˲����ķ���Ҫ��\n");
		}
		if (me->is_busy()||me->query_condition("job_busy"))
		{
			return notify_fail("�������ķ����ң��޷����˲����ķ���Ҫ��\n");
		}
		if (arg=="���������"||arg=="yaojue"||arg=="jingyao")
		{
			 message_vision("����$N��ϥ��������ϸ�����⡶���������ʮ�ľ���Ҫƪ����\n", me);
			//
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query("max_pot")-100 )
				return notify_fail("���ܾ������ޣ��޷��ٽ����ˡ�\n");
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
				return notify_fail("�������칦���ޣ�����������޷��ٽ����ˡ�\n");
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
				return notify_fail("�������칦���ޣ�����������޷��ٽ����ˡ�\n");
			
			if (me->query_skill("jinguan-yusuojue",1)>100 && !me->query("yusuo/degree"))
				return notify_fail("������������������ƿ������Ҫ���Ƶ�һ�عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>200 &&  (int)me->query("yusuo/degree")<2)
				return notify_fail("������������������ƿ������Ҫ���Ƶڶ��عؿڷ��ɼ���������\n");
		
			if (me->query_skill("jinguan-yusuojue",1)>300 && (int)me->query("yusuo/degree")<3)
				return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>400 && (int)me->query("yusuo/degree")<4)
				return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>500 && me->query("yusuo/degree")<5)
				return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>600 && me->query("yusuo/degree")<6)
				return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>700 && me->query("yusuo/degree")<7)
				return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>800 && me->query("yusuo/degree")<8)
				return notify_fail("������������������ƿ������Ҫ���Ƶڰ��عؿڷ��ɼ���������\n");
			if (me->query_skill("jinguan-yusuojue",1)>900 && me->query("yusuo/degree")<9)
				return notify_fail("������������������ƿ������Ҫ���Ƶھ��عؿڷ��ɼ���������\n");
			
			
			if (me->query("jing") < 50) {
				write("��ϧ��̫���ˣ��޷����о������о����������ʮ�ľ���\n");
				return 1;
			}
			if (me->query("potential")<4)
			{
				return notify_fail("������Ǳ�ܲ���,�޷�������������ʮ�ľ���\n");
			}
			me->add("potential",-2-random(3));
			me->receive_damage("jing", 20+random(10),"�������Ĺ���");
			if (me->query("ggs/started")&&!random(4))
			{
				i=i*2+random(i);
				tell_object(me,"���ڹ�ȼӳ��£�������Դ�����ѧ�����°빦����\n");
			}
			me->improve_skill("jinguan-yusuojue", i);
			if (random(10)<3)
			{
				me->add_busy(1);
			}
			
			write("���缢�ƿʣ���������һЩ�����������ʮ�ľ����ļ��ɡ�\n");

		}
		return 1;


}

int do_ketou(string arg)
{
        object sword;
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ģ�\n");


        if ( me->query("family/family_name")!="ȫ���"  ) 
                return notify_fail("�㿴���������˵Ļ���������������Ⱥ��������µľ�����ɣ����ɵð���һ�ݡ�\n"); 
                
        if ( me->query("qi") <= 50)
        	      return notify_fail("���㵱ǰ������״����ȥ��Ϣ�ɡ�"); 
        	      
     //  sword= new(BINGQI_D("sword/qixing-jian"));
		
		if (me->query_temp("quest/qz/htz/chongyang/findzi")&&arg=="��ש")
		{
			message_vision(HIW"$N������ԥ�������Զ�أ�������ǰ�м��ǿ���ש�ϡ�\n"NOR,me);

			message_vision(HIC"�������ˡ����������죬$N��Ȼ��ʶ����ذ��¿����ǿյģ����򲻻���˻��졣\n"NOR,me);
			message_vision(HIY"�����д����˻��أ�ֻ�������ҡ����죬��ǰ�Գ�һ����ڣ�����һ�˽��룡\n"NOR,me);
			add("exits", ([
               // "out" : __DIR__"xiaolu3",
				"rukou" : __DIR__"didao1",				
			]));
			call_out("remove_rukou",5);
			return 1;
		}
        if( me->query_temp("ketou") && arg =="��")
        {
            message_vision(HIG"$N����ǰȥ�����������ʦ���񣬹���������ͷ��\n"NOR,me);
            if (me->query_temp("quest/qz/htz/chongyang/askma"))
            {
	
				message_vision(HIC"$N�����ڵأ��۽����ӣ���Ȼ�������񰸽����Ͽ��˼���С�֡��������������ģ�������ϣ�ߵ�����Ρ���\n"NOR,me);
				message_vision(HIC"$N������������ש����������������ǡ�����Լ�Ŀǰ����Ե��ǿ���ש��\n"NOR,me);

				me->set_temp("quest/qz/htz/chongyang/findzi",1);
            }
			
            me->set_temp("get_sword",1);
            return 1;
         }
          else
          {
             message_vision("$N��������������ǰ�������Ϲ���������������ʦ�������������ͷ��\n", me);
             me->add_temp("ketou", 1);
			 if (random(me->query_temp("ketou"))>10
				 &&random(me->query("kar"))>20 )
			 {
				 message_vision(HIC"$Nn������������ͷ̧ͷ˲�䣬��Ȼ���է�֣��������˵���ָ�����ƺ���Щ�쳣��\n"NOR, me);
				 me->set_temp("qz/ketouok",1);
			 }
             return 1;
          }
	   //��ͷ�����������

 }
 
int remove_rukou()
{
	
	write("һ�Ṧ�򣬻����������죬�ָ�ԭ���������ʧ��\n");
	delete("exits/rukou");
	
	return 1;
}
//���칦quest�Ĵ�����
//��������Ҳ������ô���õ�

int do_fan(string arg)
{
        object paper;
        object me = this_player();

        if (!arg || arg != "���ؾ���")
                return notify_fail("��Ҫ��ʲô��\n");
		
		if (me->query_skill("xiantian-gong",1)<450)
		{
			return notify_fail("������칦����450���޷�����������\n");
		}

		if (me->query_skill("quanzhen-jianfa",1)<450)
		{
			return notify_fail("���ȫ�潣������450���޷�����������\n");
		}
		if (me->query_skill("taoism",1)<200)
		{
			return notify_fail("��ĵ�ѧ�ķ�����200���޷�����������\n");
		}
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ģ�\n");
   
        if ( !(me->query("family/family_name")=="ȫ���") ) 
                return notify_fail("������ķ����˼�ҳ������������������֮������ֻ����������������˽⣬��Ȼ��ζ��\n"); 
               
       if ( !me->query_temp("ketou")  ) 
                return notify_fail("�㷭���˼�ҳ������������������֮����ֻ��������ޱȡ�\n");        

       if ( query("paper_count") <1  ) 
                return notify_fail("�㷭���˼�ҳ������������������֮����ֻ��������ޱȡ�\n");        

		//������ƪ����

        if ( me->query_skill("xiantian-gong", 1)>=450
			 && me->query("quest/qz/xtg/dingyang/start")  //Ҫ�д��������õ�
			 && me->query_skill("taoism", 1)>=200 
             && me->query_skill("quanzhen-jianfa", 1)>=450 
			 && random(50) >=25
			 && !me->query_temp("quanzhen/force")
             && !me->query("quanzhen/force") ) 
        {
                paper=new(__DIR__"obj/xtg_book");
                if ( !paper ) return 1;

                add("paper_count", -1);
                me->set_temp("quanzhen/force", 1);

                message_vision(HIR"$N��ϸ�ķ����Ŷ������ص�ѧ���䣬��Ȼ���㷢������һ�����ƺ�����һС��˿�\n"NOR,me);
                write(MAG"����ϸ�Ľ�˿����һ����������������ļ����������ķ����ƺ������칦һ����У���ȴ������¡�\n"NOR);
                message_vision("$N��æ�������պá�\n",me);
				paper->set("owner",me->query("id"));
                paper->move(me, 1);
              return 1;
        } 
       else  
            {   me->add_temp("ketou",-1);
              message_vision("$N����ķ����˼�ҳ������������������֮������ֻ����������������˽⣬��Ȼ��ζ��\n",me); 
              return 1;
              }

}

