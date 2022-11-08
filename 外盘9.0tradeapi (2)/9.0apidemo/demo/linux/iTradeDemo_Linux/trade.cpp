#include "Trade.h"
#include "iTapAPIError.h"
#include "TradeConfig.h"
#include <iostream>
#include <string.h>

using namespace std;

Trade::Trade(void) :
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
}


Trade::~Trade(void)
{
}


void Trade::SetAPI(ITapTradeAPI *pAPI)
{
	m_pAPI = pAPI;
}


void Trade::printHelp()
{
	cout << "---------------------------------\n"
		<< "iTapTradeAPI_Demo CMD\n"
		<< "--->1 : order test \n"
		<< "--->2 : cancle order test\n"
		<< "--->3 : qry fund test\n"
		<< "--->4 : qry hold test\n"
		<< "--->5 : modify order test\n"
		<< "--->6 : qry commdity\n"
		<< "--->7 : qry Order\n"
		<< "--->8 : qry Fill\n"
		<< "--->H : help\n"
		<< "----------------------------------\n"
		<< endl;
}

void Trade::loopCmd()
{
	this->printHelp();
	while (1)
	{
		char cmd;
		cin >> cmd;
		switch (cmd)
		{
		case '1': this->t_insertOrder(); break;
		case '2': this->t_canncelOrder(); break;
		case '3': this->t_qryFund(); break;
		case '4': this->t_qryPostion(); break;
		case '5': this->t_modify(); break;
		case '6': this->t_qryCommdity(); break;
		case '7': this->t_qryOrder(); break;
		case '8': this->t_qryfill(); break;
		case '9': this->t_qryHisOrder();break;
		case 'H': this->printHelp(); break;
		default:
			break;
		}
	}
}


void Trade::t_insertOrder()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	//�µ�
	TapAPINewOrder stNewOrder;


	strcpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);
	strcpy(stNewOrder.ExchangeNo, DEFAULT_EXCHANGE_NO);
	stNewOrder.CommodityType = DEFAULT_COMMODITY_TYPE;
	strcpy(stNewOrder.CommodityNo, DEFAULT_COMMODITY_NO);
	strcpy(stNewOrder.ContractNo, DEFAULT_CONTRACT_NO);
	stNewOrder.OrderType = DEFAULT_ORDER_TYPE;
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_SELF_ETRADER;
	stNewOrder.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	stNewOrder.OrderSide = DEFAULT_ORDER_SIDE;
	stNewOrder.OrderPrice = DEFAULT_ORDER_PRICE;
	stNewOrder.OrderQty = DEFAULT_ORDER_QTY;
	stNewOrder.IsRiskOrder=APIYNFLAG_YES;
	strcpy(stNewOrder.ClientID, "F001");
	m_uiSessionID = 0;
	TAPISTR_50 clientOrderId="";
	iErr = m_pAPI->InsertOrder(&m_uiSessionID, &clientOrderId, &stNewOrder);
	if (TAPIERROR_SUCCEED != iErr) {
		cout << "InsertOrder Error:" << iErr << endl;
		return;
	}
	cout<<clientOrderId<<endl;
}

void Trade::t_canncelOrder()
{
	TAPISTR_20 orderno;
	cout << "cancle operator :insert orderno" << endl;
	cin >> orderno;

	TapAPIOrderCancelReq req;
	memset(&req, 0, sizeof(req));
	strncpy(req.OrderNo, orderno, strlen(orderno));

	TAPIUINT32 reqid = 0;
	TAPIINT32 iErr = TAPIERROR_SUCCEED;

	iErr = m_pAPI->CancelOrder(&reqid, &req);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "cancle Error:" << iErr << endl;
	}
}

void Trade::t_qryFund()
{
	TapAPIFundReq req;
	memset(&req, 0, sizeof(req));
	strncpy(req.AccountNo, DEFAULT_ACCOUNT_NO, strlen(DEFAULT_ACCOUNT_NO));

	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryFund(&m_uiSessionID, &req);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "t_qryFund Error:" << iErr << endl;
	}
}

void Trade::t_qryPostion()
{
	TapAPIPositionQryReq req;
	memset(&req, 0, sizeof(req));
	strncpy(req.AccountNo, DEFAULT_ACCOUNT_NO, strlen(DEFAULT_ACCOUNT_NO));

	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryPosition(&m_uiSessionID, &req);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "t_qryPostion Error:" << iErr << endl;
	}

}

void Trade::t_qryfill()
{
	TapAPIFillQryReq req;
	memset(&req, 0, sizeof(req));
	strncpy(req.AccountNo, DEFAULT_ACCOUNT_NO, strlen(DEFAULT_ACCOUNT_NO));

	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryFill(&m_uiSessionID, &req);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "t_qryfill Error:" << iErr << endl;
	}

}


void Trade::t_modify()
{
	TapAPIAmendOrder req;
	TAPISTR_20	orderNo;
	TAPIREAL64 orderPrice;
	TAPIUINT32 orderQty;
	cout << "t_modify test" << endl;
	cout << "insert orderno" << endl;
	cin >> orderNo;
	cout << "insert price" << endl;
	cin >> orderPrice;
	cout << "insert qty" << endl;
	cin >> orderQty;

	strncpy(req.OrderNo, orderNo, strlen(orderNo));
	strncpy(req.ReqData.AccountNo, DEFAULT_ACCOUNT_NO, strlen(DEFAULT_ACCOUNT_NO));
	req.ReqData.OrderPrice = orderPrice;
	req.ReqData.OrderQty = orderQty;

	TAPIINT32  iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->AmendOrder(&m_uiSessionID, &req);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "t_modify Error:" << iErr << endl;
	}
}

void Trade::t_qryCommdity()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryCommodity(&m_uiSessionID);
}

void Trade::t_qryOrder()
{
	TapAPIOrderQryReq stOrder;
	TAPIINT32  iErr = TAPIERROR_SUCCEED;
	memset(&stOrder, 0, sizeof(stOrder));
		
	iErr = m_pAPI->QryOrder(&m_uiSessionID, &stOrder);
	if (iErr != TAPIERROR_SUCCEED) {
		cout << "QryHisMatch Error:" << iErr << endl;
	}

	

}

void Trade::t_qryHisOrder()
{

}

void Trade::t_vertificate(const TAPISTR_40 ContactInfo)
{
	TAPISTR_40 st_ContactInfo;
	memset(&st_ContactInfo, 0,sizeof(st_ContactInfo));
	strcpy(st_ContactInfo, ContactInfo);
	m_pAPI->RequestVertificateCode(&m_uiSessionID, st_ContactInfo);
}

void Trade::t_setVertificateCode()
{
	//cout << "��������֤����Ϣ:" << endl;
	//TAPISTR_10 VertificateCode;
	//cin >> VertificateCode;
	//m_pAPI->SetVertificateCode(VertificateCode);
}

void Trade::RunTest()
{
	if (NULL == m_pAPI) {
		cout << "Error: m_pAPI is NULL." << endl;
		return;
	}

	TAPIINT32 iErr = TAPIERROR_SUCCEED;


	//�趨������IP���˿�
	iErr = m_pAPI->SetHostAddress(DEFAULT_IP, DEFAULT_PORT);
	if (TAPIERROR_SUCCEED != iErr) {
		cout << "SetHostAddress Error:" << iErr << endl;
		return;
	}

	//��¼������
	TapAPITradeLoginAuth stLoginAuth;
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	strcpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	strcpy(stLoginAuth.Password, DEFAULT_PASSWORD);
	stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	iErr = m_pAPI->Login(&stLoginAuth);
	if (TAPIERROR_SUCCEED != iErr) {
		cout << "Login Error:" << iErr << endl;
		return;
	}


	//�ȴ�APIReady
	m_Event.WaitEvent();
	if (!m_bIsAPIReady) {
		cout << "API is not ready";
		return;
	}

	this->loopCmd();


	while (true)
	{
		m_Event.WaitEvent();
	}
}

void TAP_CDECL Trade::OnConnect()
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspLogin(TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo)
{
	if (TAPIERROR_SUCCEED == errorCode) {
		cout << "��¼�ɹ����ȴ�API��ʼ��..." << endl;

	}
	else {
		cout << "��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnContactInfo(TAPIINT32 errorCode, TAPIYNFLAG isLast, const TAPISTR_40 ContactInfo)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << ContactInfo << endl;
	this->t_vertificate(ContactInfo);
}

void TAP_CDECL Trade::OnRspRequestVertificateCode(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp * rsp)
{
	//cout << __FUNCTION__ << " is called." << endl;
	//cout << "������֤��Ȩ����ţ�"<<rsp->SecondSerialID<<"  "
	//	<< "��Ч�ڣ�" << rsp->Effective
	//	<< endl;
	//this->t_setVertificateCode();
}

void TAP_CDECL Trade::OnAPIReady(ITapTrade::TAPIINT32 errorCode)
{
	cout << "API��ʼ�����" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();
}

void TAP_CDECL Trade::OnDisconnect(TAPIINT32 reasonCode)
{
	cout << "API�Ͽ�,�Ͽ�ԭ��:" << reasonCode << endl;
}

void TAP_CDECL Trade::OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspAuthPassword(TAPIUINT32 sessionID, TAPIINT32 errorCode)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspSetReservedInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryAccount(TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryFund(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info)
{
	//cout << __FUNCTION__ << " is called." << endl;

	//cout <<"errorcode ="<<errorCode<<endl;



	cout << "������:" << info->CurrencyGroupNo << ","
		<< "����:" << info->CurrencyNo << ","
		<< "Ȩ��:" << info->Balance << ","
		<< "����:" << info->Available << ","
		<< "��LME��ӯ:" << info->PositionProfit << ","
		<< "LME��ӯ:" << info->LmePositionProfit << endl;
	if (isLast == 'Y') return;

}

void TAP_CDECL Trade::OnRtnFund(const TapAPIFundData *info)
{
	cout << __FUNCTION__ << " *********************************************is called." << endl;
}

void TAP_CDECL Trade::OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info)
{
	//cout << __FUNCTION__ << " is called." << endl;
	cout << "������:" << info->ExchangeNo << ","
		<< "Ʒ������:" << info->CommodityType << ","
		<< "Ʒ�ֱ��:" << info->CommodityNo << ","
		<< "��Լ����1:" << info->ContractNo1 << ","
		<< "ִ�м�1:" << info->StrikePrice1 << ","
		<< "���ǿ�����ʾ1:" << info->CallOrPutFlag1
		<< "��Լ����2:" << info->ContractNo2 << ","
		<< "ִ�м�2:" << info->StrikePrice2 << ","
		<< "���ǿ�����ʾ2:" << info->CallOrPutFlag2
		<< "��Լ����:" << info->ContractType << endl;
}

void TAP_CDECL Trade::OnRtnContract(const TapAPITradeContractInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspOrderAction(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderActionRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnOrder(const TapAPIOrderInfoNotice *info)

{
	cout << __FUNCTION__ << " is called." << endl;

	if (NULL == info) {
		return;
	}

	if (info->ErrorCode != 0) {
		cout << "������������һ������ί����Ϣ�Ĵ���" << info->ErrorCode << endl;
	}
	else {
		if (info->OrderInfo) {
			if (0 != info->OrderInfo->ErrorCode) {
				cout << "����ʧ�ܣ�"
					<< "������:" << info->OrderInfo->ErrorCode << ","
					<< "ί�б��:" << info->OrderInfo->OrderNo
					<< endl;
			}
			else {
				cout << "�����ɹ���"
					<< "Ʒ��:" << info->OrderInfo->CommodityNo << ","
					<< "��Լ:" << info->OrderInfo->ContractNo << ","
					<< "״̬:" << info->OrderInfo->OrderState << ","
					<< "ί�б��:" << info->OrderInfo->OrderNo << ","
					<< endl;
			}
		}
	}

}



void TAP_CDECL Trade::OnRspQryOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info)
{
	//cout << __FUNCTION__ << " is called." << endl;


	cout << "�ͻ��ʽ��ʺ�:" << info->AccountNo << ","
		<< "Ʒ�ֱ���:" << info->CommodityNo << ","
		<< "�Ƿ�T+1��Ч:" << info->AddOneIsValid << ","
		<< "�Ƿ�ΪT+1��:" << info->IsAddOne << ","
		<< endl;

}

void TAP_CDECL Trade::OnRspQryOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnFill(const TapAPIFillInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "Ʒ��" << info->CommodityNo << ","
		<< "��Լ" << info->ContractNo << ","
		<< "�ɽ���" << info->MatchPrice << ","
		<< "�ɽ���" << info->MatchQty << endl;
}

void TAP_CDECL Trade::OnRspQryPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;

	cout << "errorcode =" << errorCode << endl;


	cout << "Ʒ��" << info->CommodityNo << ","
		<< "��Լ" << info->ContractNo << ","
		<< "�ֲ���" << info->PositionQty << ","
		<< "�ֲּ�" << info->PositionPrice << endl;
	if (isLast == 'Y') return;

}

void TAP_CDECL Trade::OnRtnPosition(const TapAPIPositionInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "Ʒ��" << info->CommodityNo << ","
		<< "��Լ" << info->ContractNo << ","
		<< "�ֲ���" << info->PositionQty << ","
		<< "�ֲּ�" << info->PositionPrice << endl;
}

void TAP_CDECL Trade::OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary * info)
{

}

void TAP_CDECL Trade::OnRtnPositionSummary(const TapAPIPositionSummary * info)
{

}

//void TAP_CDECL Trade::OnRspQryClose( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info )
//{
//	cout << __FUNCTION__ << " is called." << endl;
//}
//
//void TAP_CDECL Trade::OnRtnClose( const TapAPICloseInfo *info )
//{
//	cout << __FUNCTION__ << " is called." << endl;
//}

void TAP_CDECL Trade::OnRtnPositionProfit(const TapAPIPositionProfitNotice *info)
{
	//cout << __FUNCTION__ << " is called." << endl;
}
void TAP_CDECL Trade::OnRspQryCurrency(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICurrencyInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnTradeMessage(const TapAPITradeMessage *info)
{
}

void TAP_CDECL Trade::OnRspQryHisOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisOrderQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryHisOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisOrderProcessQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryHisMatch(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisMatchQryRsp *info)
{
	if (errorCode==0)
	{
		cout << __FUNCTION__ << " is called." << endl;
		cout << "��������" << info->SettleDate << ","
			<< "�ͻ��ʽ��˺�" << info->AccountNo << endl;
	}
	else
	{
		cout << "��ѯ����:" << errorCode << endl;
	}
	
}

void TAP_CDECL Trade::OnRspQryHisPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisPositionQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryHisDelivery(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisDeliveryQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryAccountCashAdjust(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountCashAdjustQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryBill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *info)
{
}

void TAP_CDECL Trade::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
{
}

void TAP_CDECL Trade::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
{
}

void TAP_CDECL Trade::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
{

}

void TAP_CDECL Trade::OnRspHKMarketOrderInsert(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderMarketInsertRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspHKMarketOrderDelete(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderMarketDeleteRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnHKMarketQuoteNotice(const TapAPIOrderQuoteMarketNotice * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspOrderLocalRemove(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderLocalRemoveRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspOrderLocalInput(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderLocalInputRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspOrderLocalModify(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderLocalModifyRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspOrderLocalTransfer(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIOrderLocalTransferRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspFillLocalInput(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIFillLocalInputRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage * info)
{
}

void TAP_CDECL Trade::OnRspFillLocalRemove(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TapAPIFillLocalRemoveRsp * info)
{
	cout << __FUNCTION__ << " is called." << endl;
}



void TAP_CDECL Trade::OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradingCalendarQryRsp *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQrySpotLock(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPISpotLockDataRsp *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnSpotLock(const ITapTrade::TapAPISpotLockDataRsp *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}