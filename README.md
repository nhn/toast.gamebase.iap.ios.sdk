# ToastGamebaseIAP 사용 가이드

## ToastGamebaseIAP의 구성

* ToastGamebaseIAP
    * [ToastIAP] ToastIAP.framework (0.14.1 ~) `필수`
        * [ToastCore] ToastCore.framework
            * [ToastCommon] ToastCommon.framework
    * [ToastOngate] ToastOngate.framework (0.9.0 ~) `선택`

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
pod 'ToastGamebaseIAP'
pod 'ToastOngate', '0.9.0'
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
#import <ToastIAP/ToastIAP.h>
#import <ToastOngate/ToastOngate.h>
```

## API 사용 가이드

### 초기화

#### Configuration

* ToastGamebaseIAP는 Configuration을 사용하여 초기화 할 수 있습니다.

##### API 명세

``` objc
@interface ToastGamebaseIAPConfiguration : NSObject <NSCoding, NSCopying>

//ToastOngate
@property (nonatomic, copy) NSString *ongateAppID;
@property (nonatomic, copy) NSString *ongateUserID;
@property (nonatomic) NSInteger ongateServiceZone;

//ToastIAP
@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *appKey;
@property (nonatomic) NSInteger serviceZone;

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                                 userID:(NSString *)userID
                            serviceZone:(ToastGamebaseServiceZone)serviceZone
                            ongateAppID:(NSString *)ongateAppID
                           ongateUserID:(NSString *)ongateUserID
                      ongateServiceZone:(ToastGamebaseServiceZone)ongateServiceZone;

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                                 userID:(NSString *)userID
                            serviceZone:(ToastGamebaseServiceZone)serviceZone;

@end
```

##### API 사용 예

``` objc
// Ongate와 함께 사용할 경우 
ToastGamebaseIAPConfiguration *configuration = [ToastGamebaseIAPConfiguration configurationWithAppKey:appKey
                                                                                               userID:userID
                                                                                          serviceZone:ToastGamebaseServiceZoneReal
                                                                                          ongateAppID:ongateAppID
                                                                                         ongateUserID:ongateUserID
                                                                                    ongateServiceZone:ToastGamebaseServiceZoneReal];

// ToastIAP 만 사용할 경우 
ToastGamebaseIAPConfiguration *configuration = [ToastGamebaseIAPConfiguration configurationWithAppKey:appKey
                                                                                               userID:userID
                                                                                          serviceZone:ToastGamebaseServiceZoneReal];
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

- (void)didReceivePurchaseResult:(ToastGamebasePurchaseResult *_Nonnull)purchase forStore:(NSString *_Nonnull)store;
- (void)didFailPurchaseProduct:(NSString *_Nonnull)productIdentifier forStore:(NSString *_Nonnull)store error:(NSError *_Nonnull)error;

@end
```

##### API 사용 예

``` objc
- (void)didFailPurchaseProduct:(NSString *)productIdentifier forStore:(NSString *)store error:(NSError *)error {

    NSLog(@"didFailPurchaseProduct : %@", productIdentifier);
    NSLog(@"didFailPurchaseProduct : %@", error);

}

- (void)didReceivePurchaseResult:(ToastGamebasePurchaseResult *)purchase forStore:(NSString *)store {

    NSLog(@"didReceivePurchaseResult : %@", purchase);
    NSLog(@"didReceivePurchaseResult : %@", store);
}
```

#### Observer

* SDK를 통해 요청한 결제는 등록된 Observer로 결과가 전달 됩니다.

##### API 명세

``` objc
// 요청한 결제의 성공 결과만을 받기 원할 경우 
static NSString *const ToastGamebaseDidReceivePurchaseResultNotification = @"ToastGamebaseDidReceivePurchaseResult";

// 요청한 결제의 실패 결과만을 받기 원할 경우 
static NSString *const ToastGamebaseDidFailPurchaseProductNotification = @"ToastGamebaseDidFailPurchaseProduct";

// 요청한 결제의 성공, 실패 결과를 함께 받기 원할 경우 
static NSString *const ToastGamebasePurchaseResultNotification = @"ToastGamebasePurchaseResultNotification";
```

##### API 사용 예

```objc
//...
[[NSNotificationCenter defaultCenter] addObserver:instance
                                         selector:@selector(success:)
                                             name:ToastGamebaseDidReceivePurchaseResultNotification
                                           object:nil];

[[NSNotificationCenter defaultCenter] addObserver:instance
                                         selector:@selector(fail:)
                                             name:ToastGamebaseDidFailPurchaseProductNotification
                                           object:nil];

[[NSNotificationCenter defaultCenter] addObserver:instance
                                         selector:@selector(result:)
                                             name:ToastGamebasePurchaseResultNotification
                                           object:nil];
//...


- (void)success:(NSNotification *)notification {
    NSDictionary *result = [[notification userInfo] copy];

    NSString *store = [result objectForKey:@"Store"];
    ToastGamebasePurchaseResult * purchase = [result objectForKey:@"ToastGamebasePurchaseResult"];

    NSLog(@"[success Notification] ToastGamebasePurchaseResult : %@", purchase);
    NSLog(@"[success Notification] Store : %@", store);
}

- (void)fail:(NSNotification *)notification {
    NSDictionary *result = [[notification userInfo] copy];

    NSString *store = [result objectForKey:@"Store"];
    NSError * error = [result objectForKey:@"Error"];
    NSString *productIdentifier = [result objectForKey:@"ProductIdentifier"];

    NSLog(@"[fail Notification] ProductIdentifier : %@", productIdentifier);
    NSLog(@"[fail Notification] Store : %@", store);
    NSLog(@"[fail Notification] Error : %@", error);
}

- (void)result:(NSNotification *)notification {
    NSDictionary *result = [[notification userInfo] copy];

    BOOL success = [[result objectForKey:@"Success"] boolValue];
    ToastGamebasePurchaseResult *purchase = [result objectForKey:@"ToastGamebasePurchaseResult"];
    NSString *productIdentifier = [result objectForKey:@"ProductIdentifier"];
    NSString *store = [result objectForKey:@"Store"];
    NSError *error = [result objectForKey:@"Error"];

    NSLog(@"[result Notification] Success : %@", success ? @"YES" : @"NO");
    NSLog(@"[result Notification] ToastGamebasePurchaseResult : %@", purchase);
    NSLog(@"[result Notification] ProductIdentifier : %@", productIdentifier);
    NSLog(@"[result Notification] Store : %@", store);
    NSLog(@"[result Notification] Error : %@", error);
}
```

### 상품 목록 조회

* IAP 콘솔에 등록되어 있는 상품 중 사용 여부 설정이 USE인 상품의 목록을 조회합니다.
* 스토어(Apple)에서 상품 정보를 획득하지 못한 상품은 invalidProducts 항목으로 표시됩니다.

##### API 명세

``` objc
static NSString *const ToastGamebaseStoreAppStore   = @"APPSTORE";
static NSString *const ToastGamebaseStoreOngate     = @"ONGATE";


+ (void)requestProductsForStore:(NSString *)store
          withCompletionHandler:(nullable void (^)(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestProductsForStore:self.storeType
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
typedef NS_ENUM(NSInteger, ToastGamebaseProductType) {
    ToastGamebaseProductTypeUnknown                     = 0,
    ToastGamebaseProductTypeConsumable                  = 1,
    ToastGamebaseProductTypeAutoRenewableSubscription   = 2,
};
```

### 상품 구매

* 구매 결과는 설정된 Observer를 통해 전달됩니다.
* 구매 진행 중에 앱이 종료되거나 네트워크 오류 등으로 구매가 중단되었을 경우 앱이 재실행되면, IAP SDK를 초기화할 때 구매 재처리를 진행합니다.

#### 상품 객체를 이용한 구매 요청

* 상품 목록 조회 결과의 ToastGamebaseProduct 객체를 이용해 구매를 요청합니다.

##### API 명세

``` objc
+ (void)purchaseForStore:(NSString *)store
             withProduct:(ToastGamebaseProduct *)product;

+ (void)purchaseForStore:(NSString *)store
   withProductIdentifier:(NSString *)productIdentifier;
```

##### API 사용 예

``` objc
@property (nonatomic) NSArray <ToastProduct *> *products;

// 상품 목록 조회
[ToastGamebaseIAP requestProductsForStore:self.storeType
                    withCompletionHandler:^(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error) {

    if (error == nil) {
        // 구매 가능한 상품 목록 저장
        self.products = response.products;

    } else {
        NSLog(@"Failed to request products: %@", error);
    }
}];



// 상품 구매 요청
[ToastGamebaseIAP purchaseForStore:self.storeType withProduct:[self.products objectAtIndex:0]];

```

#### 상품 ID를 이용한 구매 요청

* 서비스에서 별도로 상품 목록을 관리하고 있다면, 상품 ID만을 이용해 구매를 요청합니다.
* 구매할 수 없는 상품이면 Observer를 통해 구매 불가 상품임을 나타내는 오류가 전달됩니다.

##### API 명세

``` objc
+ (void)purchaseWithProductIdentifier:(NSString *)productIdentifier;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP purchaseForStore:self.storeType withProductIdentifier:PRODUCT_IDENTIFIER];
```

### 활성화된 구매 목록 조회

> ToastIAP(AppStore)에서만 지원하는 기능입니다.

* 현재 사용자 ID에 활성화된 구매(만료되지 않고 구독 중인 구독 상품) 목록을 조회합니다.
* 사용자 ID가 같다면 Android에서 구매한 구독 상품도 조회됩니다.

##### API 명세

``` objc
+ (void)requestActivePurchasesForStore:(NSString *)store
                 withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestActivePurchasesForStore:self.storeType 
                           withCompletionHandler:^(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error) {

    if(error == nil) {
        NSLog(@"requestActivePurchases : %@", purchases);
    }else {
        NSLog(@"requestActivePurchases : %@", error);
    }
}];
```

### 구매 복원

> ToastIAP(AppStore)에서만 지원하는 기능입니다.

* 현재 사용자 ID에서 구매된 항목 중 복원 가능한 구매 목록을 조회합니다.

##### API 명세

``` objc
+ (void)restoreForStore:(NSString *)store
  withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
ToastGamebaseIAP restoreForStore:self.storeType
           withCompletionHandler:^(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error) {

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

##### API 명세

``` objc
+ (void)requestConsumablePurchasesForStore:(NSString *)store
                     withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error))completionHandler;
```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestConsumablePurchasesForStore:self.storeType 
                               withCompletionHandler:^(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error) {

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

```

##### API 사용 예

``` objc
[ToastGamebaseIAP requestConsumablePurchasesForStore:self.storeType
                               withCompletionHandler:^(NSArray<ToastGamebasePurchaseResult *> * _Nullable purchases, NSError * _Nullable error) {

    for (int i=0; i<purchases.count; i++) {

        ToastGamebasePurchaseResult *result = [purchases objectAtIndex:i];

        [ToastGamebaseIAP consumeForStore:self.storeType
                           purchaseResult:result
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
