# ToastGamebaseIAP 사용 가이드

## ToastGamebaseIAP의 구성

* ToastGamebaseIAP
    * [ToastIAP] ToastIAP.framework (0.18.0 ~) `필수`
        * [ToastCore] ToastCore.framework
            * [ToastCommon] ToastCommon.framework
    * [ToastOngate] ToastOngate.framework (0.9.3 ~) `선택`

| SDK | Cocoapods Pod Name | Framework | Dependency | Etc |
| --- | ------------------ | --------- | ---------- | --- |
| TOAST Gamebase IAP SDK | ToastGamebaseIAP | ToastGamebaseIAP.framework | ToastIAP | OTHER_LDFLAGS = ("-ObjC"); |
| TOAST IAP SDK | ToastIAP | ToastIAP.framework | ToastCore<br>ToastCommon | OTHER_LDFLAGS = ("-ObjC","-lc++" ); |
| Ongate SDK | ToastOngate | ToastOngate.framework | - | OTHER_LDFLAGS = ("-ObjC"); |

## TOAST SDK를 Xcode 프로젝트에 적용

### 1\. Cococapods를 사용해 TOAST SDK 적용

Podfile을 생성하여 TOAST SDK에 대한 Pod을 추가합니다.

``` podspec
platform :ios, '8.0'
use_frameworks!

target '{YOUR PROJECT TARGET NAME}' do
    pod 'ToastGamebaseIAP', '0.9.7'
    pod 'ToastIAP'
    pod 'ToastOngate'
end
```

### 2\. 바이너리를 직접 적용

1. Download 한 바이너리를 프로젝트에 import 합니다.
2. **Build Settings**의 **Other Linker Flags**에 \*\*\-lc\+\+\*\*와 **-ObjC** 항목을 추가합니다.
* **Project Target > Build Settings > Linking > Other Linker Flags**를 클릭해 추가할 수 있습니다.

![other_linker_flags](http://static.toastoven.net/toastcloud/sdk/ios/overview_settings_flags.png)

### import

생성된 워크스페이스 또는 프로젝트를 열어 사용할 SDK를 가져옵니다(import).

``` objc
#import <ToastGamebaseIAP/ToastGamebaseIAP.h>
#import <ToastCore/ToastCore.h>
#import <ToastIAP/ToastIAP.h>
#import <ToastOngate/ToastOngate.h>
```

## API 사용 가이드

## 서비스 로그인

* TOAST SDK에서 제공하는 모든 상품(IAP, Log & Crash, Push등)은 같은 사용자 ID 하나만 사용합니다.

### 로그인

`사용자 ID가 설정되지 않은 상태에서는 구매, 활성화된 상품 조회, 미소비 내역 조회 기능을 사용할 수 없습니다.`

``` objc
// 서비스 로그인 완료 후 사용자 ID 설정
[ToastSDK setUserID:@"INPUT_USER_ID"];
```

### 로그아웃

``` objc
// 서비스 로그아웃 완료 후 사용자 ID를 nil로 설정
[ToastSDK setUserID:nil];
```

### 초기화

#### Configuration

* ToastGamebaseIAP는 Configuration을 사용하여 초기화 할 수 있습니다.

* 초기화 이후에 동작하는 미완료 결제의 재처리와 프로모션 상품의 구입을 위해 초기화 이전에 UserID 설정이 필요합니다. 

##### API 명세

``` objc

@interface ToastGamebaseIAPConfiguration : NSObject <NSCoding, NSCopying>

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                            serviceZone:(ToastGamebaseServiceZone)serviceZone;

- (void)setExtraObject:(NSDictionary *)object forStore:(NSString *)store;

@end
```

##### API 사용 예

``` objc

ToastGamebaseIAPConfiguration *configuration = [ToastGamebaseIAPConfiguration configurationWithAppKey:appKey
                                                                                          serviceZone:ToastGamebaseServiceZoneReal];


NSMutableDictionary *ongateExtras = [[NSMutableDictionary alloc]init];
[ongateExtras setObject:ongateAppID  forKey:kToastProviderAppID];
[ongateExtras setObject:ongateUserID forKey:kToastProviderUserID];

[configuration setExtraObject:ongateExtras forStore:ToastGamebaseStoreOngate];

```

#### Init

* 생성한 Configuration으로 ToastGamebaseIAP SDK를 초기화 합니다.

##### API 명세

``` objc
+ (void)setDelegate:(id<ToastGamebaseInAppPurchaseDelegate>)delegate;

+ (void)initWithConfiguration:(ToastGamebaseIAPConfiguration *)configuration;

+ (void)initWithConfiguration:(ToastGamebaseIAPConfiguration *)configuration
                     delegate:(id<ToastGamebaseInAppPurchaseDelegate>)delegate;
```

##### API 사용 예

``` objc
//...
// Delegate와 SDK 초기화를 따로 할 경우 
[ToastGamebaseIAP setDelegate:self];
//...
[ToastGamebaseIAP initWithConfiguration:configuration];
//...

//...
// 초기화시에 Delegate도 함께 설정 할 경우 
[ToastGamebaseIAP initWithConfiguration:configuration delegate:self];
//...
```

#### Delegate

* SDK를 통해 요청한 결제가 아닐 경우 Delegate를 통해 결과가 전달 됩니다.
* Promotion (AppStore Purchase)

##### API 명세

``` objc
@protocol ToastGamebaseInAppPurchaseDelegate <NSObject>

- (void)didReceivePurchaseResultForStore:(ToastGamebaseStoreCode _Nonnull)store
                               isSuccess:(BOOL)isSuccess
                                purchase:(ToastGamebasePurchase *_Nullable)purchase
                               productID:(NSString * _Nonnull)productID
                                   error:(NSError *_Nullable)error;

@end
```

##### API 사용 예

``` objc

- (void)didReceivePurchaseResultForStore:(ToastGamebaseStoreCode _Nonnull)store
                               isSuccess:(BOOL)isSuccess
                                purchase:(ToastGamebasePurchase *_Nullable)purchase
                               productID:(NSString * _Nonnull)productID
                                   error:(NSError *_Nullable)error {

    if (isSuccess) {
        NSLog(@"Success Store : %@", store);
        NSLog(@"Success Purchase : %@", purchase);
    }else {
        NSLog(@"Fail Store : %@", store);
        NSLog(@"Fail ProductID : %@", productID);
        NSLog(@"Fail Error : %@", error);
    }
}
```

### 상품 목록 조회

* IAP 콘솔에 등록되어 있는 상품 중 사용 여부 설정이 USE인 상품의 목록을 조회합니다.
* 스토어(Apple)에서 상품 정보를 획득하지 못한 상품은 invalidProducts 항목으로 표시됩니다.

##### API 명세

``` objc
extern NSString *const ToastGamebaseStoreAppStore;
extern NSString *const ToastGamebaseStoreOngate;


+ (void)requestProductsForStore:(NSString *)store
          withCompletionHandler:(nullable void (^)(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestProductsForStore:self.store
                    withCompletionHandler:^(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error) {

    if(error == nil) {    
        NSLog(@"response : %@", response);
        NSLog(@"response.products : %@", response.products);
        NSLog(@"response.invalidProducts : %@", response.invalidProducts);
    }else {
        NSLog(@"error : %@", error);
    }
}];
```

##### 상품 종류

* `AppStore의 자동 갱신형 구독 상품의 업그레이드, 다운그레이드, 수정 기능은 지원하지 않습니다.`
* 하나의 구독 그룹에 하나의 상품만 등록해야 합니다.
* Ongate의 경우 소비성 상품만 지원합니다.

``` objc
typedef NSString *ToastGamebaseProductType NS_STRING_ENUM;
extern ToastGamebaseProductType const ToastGamebaseProductTypeUnknown;
extern ToastGamebaseProductType const ToastGamebaseProductTypeConsumable;
extern ToastGamebaseProductType const ToastGamebaseProductTypeAutoRenewableSubscription;
extern ToastGamebaseProductType const ToastGamebaseProductTypeConsumableSubscription;
```

### 상품 구매

* 구매 진행 중에 앱이 종료되거나 네트워크 오류 등으로 구매가 중단되었을 경우에는 재처리를 통해 결제가 완료됩니다. 
    * 재처리 동작 시점 
        * 앱 재실행 후 IAP SDK 초기화
        * Background -> Foreground 전환 
        * 결제 요청
        * 미소비 내역 조회
* String 형식의 payload와 gamebasePayload를  추가 할 수 있습니다. (ToastIAP Only)
* 추가한 정보는 결제 결과와 함께 반환됩니다. 
> `AppStore에서 실패 처리된 결제가 성공으로 정정되어 재반환된 경우에는 재처리를 통해 결제가 완료되며 결제 요청시 입력한 추가 정보가 유실 됩니다.`

#### 상품 객체를 이용한 구매 요청
* 상품 목록 조회 결과의 ToastGamebaseProduct 객체를 이용해 구매를 요청합니다.

##### API 명세

``` objc
typedef void (^ToastGamebasePurchaseHandler)(ToastGamebaseStoreCode _Nonnull store,
                                             BOOL isSuccess,
                                             ToastGamebasePurchase *_Nullable purchase,
                                             NSString *_Nonnull productID,
                                             NSError* _Nullable error);

+ (void)purchaseForStore:(ToastGamebaseStoreCode)store
                 product:(ToastGamebaseProduct *)product
                 payload:(nullable NSString *)payload
         gamebasePaylaod:(nullable NSString *)gamebasePayload
   withCompletionHandler:(ToastGamebasePurchaseHandler)completionHandler;
```

##### API 사용 예

``` objc
@property (nonatomic) NSArray <ToastProduct *> *products;

// 상품 목록 조회
[ToastGamebaseIAP requestProductsForStore:self.store
                    withCompletionHandler:^(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error) {

    if (error == nil) {
        // 구매 가능한 상품 목록 저장
        self.products = response.products;

    } else {
        NSLog(@"Failed to request products: %@", error);
    }
}];



// 상품 구매 요청
 [ToastGamebaseIAP purchaseForStore:store
                            product:[self.products objectAtIndex:0]
                            payload:payload
                    gamebasePaylaod:gamebasePayload
              withCompletionHandler:^(NSString* store, BOOL isSuccess, ToastGamebasePurchase * _Nullable purchase, NSString *_Nonnull productID, NSError * _Nullable error)
{            
     NSLog(@"[result Callback] Store : %@", store);
     NSLog(@"[result Callback] Success : %@", isSuccess ? @"YES" : @"NO");
     NSLog(@"[result Callback] ToastGamebasePurchaseResult : %@", purchase);
     NSLog(@"[result Callback] Error : %@", error);
}];

```

#### 상품 ID를 이용한 구매 요청

* 서비스에서 별도로 상품 목록을 관리하고 있다면, 상품 ID만을 이용해 구매를 요청합니다.

##### API 명세

``` objc

typedef void (^ToastGamebasePurchaseResultHandler)(NSString *_Nonnull store,
                                                   BOOL isSuccess,
                                                   ToastGamebasePurchase *_Nullable purchase,
                                                   NSString *_Nonnull productID,
                                                   NSError* _Nullable error);

+ (void)purchaseForStore:(ToastGamebaseStoreCode)store
               productID:(NSString *)productID
                 payload:(nullable NSString *)payload
         gamebasePaylaod:(nullable NSString *)gamebasePayload
   withCompletionHandler:(ToastGamebasePurchaseHandler)completionHandler;
```

##### API 사용 예

``` objc

[ToastGamebaseIAP purchaseForStore:store
                            productID:product.productID
                            payload:payload
                    gamebasePaylaod:gamebasePayload
                withCompletionHandler:^(NSString* store, BOOL isSuccess, ToastGamebasePurchase * _Nullable purchase, NSString *_Nonnull productID, NSError * _Nullable error) {

    NSLog(@"[result Callback] Store : %@", store);
    NSLog(@"[result Callback] Success : %@", isSuccess ? @"YES" : @"NO");
    NSLog(@"[result Callback] ToastGamebasePurchaseResult : %@", purchase);
    NSLog(@"[result Callback] Error : %@", error);

}];

```

### 활성화된 구독 목록 조회

> ToastIAP(AppStore)에서만 지원하는 기능입니다.

* 현재 사용자 ID 기준으로 활성화된 구독 목록을 조회합니다.
* 결제가 완료된 구독 상품(자동 갱신형 구독, 자동 갱신형 소비성 구독 상품)은 만료되기 전까지 계속 조회할 수 있습니다. 
* 사용자 ID가 같다면 Android에서 구매한 구독 상품도 조회됩니다.

##### API 명세

``` objc
+ (void)requestActivatedPurchasesForStore:(NSString *)store
                    withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestActivatedPurchasesForStore:self.store
                              withCompletionHandler:^(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error) {

    if(error == nil) {
        NSLog(@"requestActivatedPurchases : %@", purchases);
    }else {
        NSLog(@"requestActivatedPurchases : %@", error);
    }
}];
```

### 구매 복원

> ToastIAP(AppStore)에서만 지원하는 기능입니다.

* 사용자의 AppStore 계정으로 구매한 내역을 기준으로 구매 내역을 복원하여 IAP 콘솔에 반영합니다. 
* 구매한 구독 상품이 조회되지 않거나 활성화 되지 않을 경우 사용합니다.
* 구매 복원이 완료된 후에 복원된 결제건의 정보를 반환합니다.
* 자동 갱신형 소비성 구독 상품의 경우 반영되지 않은 구매 내역이 존재할 경우 복원 후 미소비 구매 내역에서 조회 가능합니다.

##### API 명세

``` objc
+ (void)restoreForStore:(NSString *)store
  withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
ToastGamebaseIAP restoreForStore:self.store
           withCompletionHandler:^(NSArray<ToastGamebasePurchaset *> * _Nullable purchases, NSError * _Nullable error) {

    if(error == nil) {
        NSLog(@"restore : %@", purchases);
    }else {
        NSLog(@"restore : %@", error);
    }
}];

```

### 미소비 구매 내역 조회

* 소비성 상품의 경우 상품 지급 후에 소비(consume) 처리를 해야 합니다.
* 소비 처리되지 않은 구매 내역을 조회합니다.
* 자동 갱신형 소비성 구독 상품은 갱신 결제가 발생할 때마다 미소비 구매 내역에서 조회 가능합니다.
##### API 명세

``` objc
+ (void)requestConsumablePurchasesForStore:(NSString *)store
                     withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestConsumablePurchasesForStore:self.store
                               withCompletionHandler:^(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error) {

    if (error == nil) {
        NSLog(@"%@", purchases);
    } else {
        NSLog(@"%@", error);
    }
}];
```

### 소비성 상품 소비

* 소비성 상품의 경우 서비스에 상품 지급 후에 REST API 혹은 SDK의 Consume API로 소비 처리를 해야 합니다.

##### API 명세

``` objc
+ (void)consumeForStore:(ToastGamebaseStoreCode)store
               purchase:(ToastGamebasePurchase *)purchase
  withCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestConsumablePurchasesForStore:self.store
                               withCompletionHandler:^(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error) {

    for (int i=0; i<purchases.count; i++) {

        ToastGamebasePurchase *result = [purchases objectAtIndex:i];

        [ToastGamebaseIAP consumeForStore:self.store
                                 purchase:result
                    withCompletionHandler:^(NSError * _Nullable error) {
                    
            NSLog(@"consumeWithStore : %@ \n %@", result, error);

            if(error == nil) {
                NSLog(@"Success Consume : %@", result ];
            }else {
                NSLog(@"Fail  Consume : %@", error ];
            }
        }];
    }
}];    
```

### (구)IAP SDK 호환성 유지

* (구)IAP SDK와의 호환성을 유지할 수 있게 (구)IAP SDK에서 생성된 미완료 구매 건의 재처리 기능을 제공합니다.
* 자세한 내용은 다음 페이지에서 확인 가능합니다.
* https://docs.toast.com/ko/TOAST/ko/toast-sdk/iap-ios/#iap-sdk

### Error Code

* ToastGamebaseIAP 의 ErrorCode는 ToastIAP의 ErrorCode와 동일한 Code를 사용합니다.
* ToastOngate에만 존재하는 ErrorCode (60001)과 Interface 통합으로 인해 발생 할 수 있는 ErrorCode는 신규 Code를 지정하여 사용합니다.

``` objc
static NSString *const ToastGamebaseIAPErrorDomain = @"com.toast.iap.gamebase";

typedef NS_ENUM(NSInteger, ToastGamebaseIAPErrorCode) {

    //ToastGamebase Error Code
    ToastGamebaseIAPErrorCodeStoreNotMatched         = 10001,

    ToastGamebaseIAPErrorCodeNotSupportedMethod      = 10008,
    ToastGamebaseIAPErrorCodeNotImportedFramework    = 10009,

    //ToastGamebase Ongate Only Code
    ToastGamebaseIAPErrorOngateCashInsufficient      = 60001,
};
```
