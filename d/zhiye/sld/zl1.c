// zl1.c
// ����1
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
���ﵽ�����Ǹ߿ɼ�������ӣ���̫������ס�ˣ���λ�ӷ嶥����ʱ
���Դ������磬���������ļ�����һ�������ĺõط���ż�������粻֪��
�������һ��ҩ��,���ֱ����ƺ���һƬҩ�ԡ�
long);
	set("exits",([
	    "enter" : __DIR__"tz",
           "west"  : __DIR__"zl2",
		 "north"  : __DIR__"yaopu",
	]));
	set("outdoors", "������");
    set("coor/x",490);
	set("coor/y",430);
    set("coor/z",80);
    setup();
}


/*
int do_to()
{
	object me;
	//string* pos=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 
	me=this_player();

	if (me->query_temp("sld/zhongyao/start"))
	{
		tell_object(me,YEL"��ʱ��һ��紵�����ƺ���"NOR)
	}

}


//����ȥҩ�̵�����
int do_to(string arg)
{//ÿ225һ�� 
	int times,ypstep;//times=0 ���� 1 �� 2 ���� 3 �� 4 ���� 5 �� 6 ���� 7 ��
	
	object me=this_player();
	string* pos=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 
	
	int * zeropos=({0,6,3,4,1,5,2,7});

	if(!arg || arg!="east" && arg!="west" && arg!="north" && arg!="south" && arg!="northeast"
	   && arg!="northwest" && arg!="southeast" && arg!="southwest" )
		return notify_fail("��Ҫ������ȥ��\n");
	//�趨����ҩ��ʱ�䣬��ʱ��ʼ
	if(!me->query_temp("yaopu/time"))
	{
		times=uptime() % 1800;
		times/=225;
		me->set_temp("yaopu/time",times);
	}
	else
		times=me->query_temp("yaopu/time",1);
	//ҩ�Ե�һ��
	ypstep=me->query_temp("yaopu/step",1);
	//·������ȷ����һ�����ߴ�������
	if(pos[(zeropos[ypstep]+times)%8]==arg)
		me->set_temp("yaopu/step",ypstep+1);
	else
		me->delete_temp("yaopu");
	
	ypstep=me->query_temp("yaopu/step",1);
	
	if(ypstep==8)
	{
		me->move(__DIR__"yaopu1");
		me->delete_temp("yaopu");
	}
	else
		tell_object(me,"������������ȥ��\n");
	return 1;
}*/
