// OBJECT:  ice.c ����
// Created by Numa 1999-12-09

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW"��ɽ���ɽӴ�����"NOR,({"zhang peng"}));
	set_weight(20000000);
     if (clonep())

        	set_default_object(__FILE__);
     	else
     	{

        	set("unit", "��");
        	set("long", "����һ����ɽ��ר�Ÿ���Ӵ���ʱ�����ų�һ�ţ�������磡������ӭ���������ǳ����֡�\n");
        	set("value", 1);
        	set("no_get", 1); 
			set("no_steal",1);
        	//set("unique",1);
        	set("location",1);
        	//set_temp("no_return",1);
        }
     	setup();  
}

