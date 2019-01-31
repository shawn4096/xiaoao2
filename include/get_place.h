// River@SJ 2001.9.27
//���group Ŀ¼������ʾ��ȷ��������  by renlai 2017/5/31

string get_place(string str)
{
	object room;
	string *place = explode(str, "/");
    string oldstr=str;
	
	str = "";
	if(place[0] == "d")
	{
	    switch(place[1]){
			case "baituo":		str = "����ɽ";		break;
			case "qixiazhen":   str = "������";		break;
			case "cangzhou":	str = "���ݳ�";		break;
			case "changan":
				 switch(place[2]) {
					case "nongtian":	str = "����ũ��";	break;
					case "sanglin":		str = "����ɣ��";	break;
					default : 			str = "������";		break;
				}
				break;
			case "changle":		str = "���ְ�";		break;
			case "chengdu":
				switch(place[2]) {
					case "gaoshan":		str = "�ɶ�����";	break;
					default : 			str = "�ɶ���";		break;
				}
				break;
			case "city": 		str = "���ݳ�";		break;
			case "dali":
				 switch(place[2]) {
					case "daliwest":	str = "�������";	break;
					case "dalisouth":	str = "�������";	break;
					case "dalieast":	str = "����Ƕ�";	break;
					case "wuliang":		str = "����ɽ";		break;
					case "dlhg":		str = "����ʹ�";	break;
					case "wangfu":		str = "��������";	break;
					case "yideng":		str = "��Դ��";		break;
					case "yuxu":		str = "�����";		break;
					default : 			str = "�����";		break;
				}
				break;
			case "death":		str = "ʮ�˲����";	break;
			case "dzd":			str = "���ǵ�";		break;
			case "emei":		str = "����ɽ";		break;
			case "fairyland":	str = "����ɽ";		break;
			case "foshan":		str = "��ɽ��";		break;
			case "fuzhou":		str = "���ݳ�";		break;
			case "quanzhen":	str = "ȫ���";		break;
			case "xiaoyao":		str = "��ң��";		break;
			case "menggu":		str = "�ɹ�";		break;
			case "gb":			str = "ؤ��";		break;
			case "group":
				switch(place[2]){
					case "entry":					
					if (room=load_object(oldstr))
					{
						str=room->query("outdoors");
					}
                    else str = "��ԭ";	break;
					default :			str = "��ԭ";		break;
				}
				break;
			case "gumu":
				switch(place[2]) {
					case "jqg":			str = "�����";		break;
					case "xuantie":		str = "��������";	break;
					default : 			str = "����ɽ";		break;
				}
				break;
			case "hengshan":	str = "��ɽ";		break;
			case "hj":			str = "�ؽ�";		break;
			case "hmy":
				switch(place[2]) {
					case "pingding":	str = "ƽ����";		break;
					default:			str = "��ľ��";		break;
				}
				break;
			case "huanghe":
				switch(place[2]) {
					case "caikuang":	str = "�ƺӿ�";	break;
					case "yyd":			str = "����";		break;
					default :			str = "�ƺ�����";	break;
				}
				break;
			case "huashan":		str = "��ɽ";		break;
			case "hz":			str = "���ݳ�";		break;
			case "henshan":		str = "��ɽ";		break;
			case "jiaxing":		str = "���˳�";		break;
			case "jingcheng":	str = "����";		break;
			case "kunlun":		str = "����ɽ";		break;
			case "lanzhou":		str = "���ݳ�";		break;
			case "meizhuang":	str = "÷ׯ";		break;
			case "miaojiang":	str = "�置";		break;
			case "menggu":		str = "�ɹ�";           break;
			case "mingjiao":
				switch(place[2]) {
					case "hdg":		str = "������";		break;
					case "hhd":		str = "����";		break;
					case "lsd":		str = "���ߵ�";		break;
					default :		str = "����";		break;
				}
				break;
			case "mr":
				switch(place[2]){
					case "yanziwu":		str = "������";		break;
					case "mtl":		str = "��٢��ɽׯ";	break;
					default :		str = "����Ľ��";	break;
				}
				break;
			case "motianya":		str = "Ħ����";  break;

			case "nanyang":		str = "������";		break;
			case "ningbo":		str = "������";		break;
			case "putian":		str = "��������";	break;
			case "plummanor":	str = "÷ׯ";   	break;
			case "shaolin":		str = "��ɽ����";	break;
			case "sld":			str = "������";		break;
			case "sjsz":		str = "�Խ�ɽׯ";	break;
			case "songshan":	str = "��ɽ";		break;
			case "suzhou":		str = "���ݳ�";		break;
			case "taihu":		str = "̫��";		break;
			case "taishan":		str = "̩ɽ";		break;
			case "tanggu" :		str = "������";		break;
			case "thd":
				switch(place[2]) {
					case "niujia":		str = "ţ�Ҵ�";		break;
					case "guiyun":		str = "����ׯ";		break;
					default:			str = "�һ���";		break;
				}
				break;
			case "tianshan":	str = "��ɽ";		break;
			case "tiezhang":	str = "����ɽ";		break;
			case "tls":			str = "������";		break;
			case "village":		str = "��ɽ��";		break;
			case "wizard":		str = "��������";	break;
			case "wudang":
				switch(place[2]) {
					case "houshan":		str = "�䵱��ɽ";	break;
					default:			str = "�䵱ɽ";		break;
				}
				break;
			case "wuguan":		str = "���";		break;
			case "was":		    str = "����";		break;
			case "xuedao":		str = "Ѫ����";		break;

			case "xiakedao":	str = "���͵�";		break;
			case "xiangyang":
				switch(place[2]) {
					case "leitai":	str = "������̨";		break;
					case "lzz":		str = "������";		break;
					default:		str = "������";		break;
				}
				break;
			case "xingxiu":
				switch(place[2]) {
					case "yili":		str = "�����";		break;
					default:			str = "���޺�";		break;
				}
				break;
			case "xueshan":
				switch(place[2]) {
					case "caoyuan":		str = "���ԭ";		break;
					default :			str = "��ѩɽ";		break;
				}
				break;
			//case "zhiye":			str = "����";			break;
			//case "xiaoyao":		str = "��ң";			break;
			default:				str = "��ԭ����";		break;
		}
	}
	else if (place[0] == "u")
	{
		str = "����";		
	}
	return str;
}
