## Classes

<dl>
<dt><a href="#sendPost">sendPost</a></dt>
<dd></dd>
<dt><a href="#sendGet">sendGet</a></dt>
<dd></dd>
<dt><a href="#checkStatus">checkStatus</a></dt>
<dd></dd>
<dt><a href="#iterationWithReplacement">iterationWithReplacement</a></dt>
<dd></dd>
<dt><a href="#iterationOverToken">iterationOverToken</a></dt>
<dd></dd>
</dl>

<a name="sendPost"></a>

## sendPost
**Kind**: global class  
<a name="new_sendPost_new"></a>

### new sendPost(parameters)
That function prepares data for request and sends POST request


| Param | Type | Description |
| --- | --- | --- |
| parameters | <code>object</code> | transaction's parameters |
| parameters.host | <code>string</code> | the part of URL |
| parameters.txdata | <code>object</code> | parameter of field data of request's body (parameters.tx) |
| parameters.tx | <code>object</code> | request's body |
| parameters.prvkey | <code>string</code> | private key of sender |
| parameters.sign | <code>string</code> | parameter of field data of request's body (this is necessary for replacement) |

<a name="sendGet"></a>

## sendGet
**Kind**: global class  
<a name="new_sendGet_new"></a>

### new sendGet(host, api, data)
GET function for getting information about transactions and tockens


| Param | Type | Description |
| --- | --- | --- |
| host | <code>string</code> | the part of URL |
| api | <code>string</code> | the part of API |
| data | <code>object</code> | GET parameters |

<a name="checkStatus"></a>

## checkStatus
**Kind**: global class  
<a name="new_checkStatus_new"></a>

### new checkStatus(hash, expected)
That function waits response's status (!== 0), meanwhile system handles it


| Param | Type | Description |
| --- | --- | --- |
| hash | <code>string</code> | hash of transaction that should be checked |
| expected | <code>number</code> | expected status of transaction |

<a name="iterationWithReplacement"></a>

## iterationWithReplacement
**Kind**: global class  
<a name="new_iterationWithReplacement_new"></a>

### new iterationWithReplacement(keys, testCase, txData)
The function for TestSuite with 'txData' that are neсessary for property 'data' in the request body


| Param | Type | Description |
| --- | --- | --- |
| keys | <code>object</code> | set of wallets |
| keys["Alice"].pubkey | <code>string</code> | public key of the user(Alice) |
| keys["Alice"].prvkey | <code>string</code> | private key of the user(Alice) |
| testCase | <code>object</code> | structure with the description and test sets of some Test Case |
| testCase.description | <code>string</code> | name of a test case and its description |
| testCase.testStruct | <code>array</code> | array of test structures |
| testCase.testStruct.description | <code>string</code> |  |
| testCase.testStruct.value | <code>\*</code> | value for replacement |
| testCase.testStruct.from | <code>string</code> | name of sender |
| testCase.testStruct.to | <code>string</code> | name of reciever |
| testCase.testStruct.ticker | <code>string</code> |  |
| testCase.testStruct.expected | <code>string</code> |  |
| txData | <code>object</code> | transaction's data, see here (https://docs.google.com/document/d/1KSeLY7j12G5Kk44gBBwW4tcXbyAgNVVj4Wq67_BSvY8/edit#heading=h.ive92cxbupie) |

<a name="iterationOverToken"></a>

## iterationOverToken
**Kind**: global class  
<a name="new_iterationOverToken_new"></a>

### new iterationOverToken(keys, testCase)
Usefull function for testing first TestSuite (sending transactions and checking wallets)


| Param | Type | Description |
| --- | --- | --- |
| keys | <code>object</code> | set of wallets |
| keys["Alice"].pubkey | <code>string</code> | public key of the user(Alice) |
| keys["Alice"].prvkey | <code>string</code> | private key of the user(Alice) |
| testCase | <code>object</code> | structure with the description and test sets of some Test Case |
| testCase.description | <code>string</code> | name of a test case and its description |
| testCase.testStruct | <code>array</code> | array of test structures |
| testCase.testStruct.description | <code>string</code> |  |
| testCase.testStruct.method | <code>\*</code> | GET(check wallet) or POST(send tx) |
| testCase.testStruct.from | <code>string</code> | name of sender |
| testCase.testStruct.to | <code>string</code> | name of reciever |
| testCase.testStruct.amount | <code>number</code> | amount of coins |
| testCase.testStruct.ticker | <code>string</code> |  |
| testCase.testStruct.expected | <code>string</code> |  |

