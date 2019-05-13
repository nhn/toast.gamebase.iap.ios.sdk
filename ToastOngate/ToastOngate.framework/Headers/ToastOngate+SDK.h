//
//  ToastOngate+SDK.h
//  ToastOngate
//
//  Created by NHNEnt on 2019. 1. 17..
//  Copyright © 2019년 NHNEnt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ToastOngateConfiguration.h"
#import "ToastOngateProduct.h"
#import "ToastOngatePurchaseResult.h"

NS_ASSUME_NONNULL_BEGIN
@protocol ToastOngatePurchaseDelegate;

/**
 # ToastOngate
 
 SDK to manage in-app-purchase for ongate.
 
 ## initialize
 * At initialization, you must register the delegate to receive the payment result as mandatory.
 
 */
@interface ToastOngate : NSObject

#pragma mark - Initializations
// SDK 초기화
/**
 Initialize SDK.
 
 @param configuration The configuration about ToastOngate.
 */
+ (void)initWithConfiguration:(ToastOngateConfiguration *)configuration;

/**
 Initialize SDK.
 
 @param configuration The configuration about ToastOngate.
 @param delegate The delegate to be executed according to the purchase result.
 */
+ (void)initWithConfiguration:(ToastOngateConfiguration *)configuration
                     delegate:(nullable id<ToastOngatePurchaseDelegate>)delegate;

/**
 Sets Delegate with a given delegate that following ToastOngatePurchaseDelegate.
 
 @param delegate The delegate that following ToastOngatePurchaseDelegate.
 */
+ (void)setDelegate:(nullable id<ToastOngatePurchaseDelegate>)delegate;

#pragma mark - Ongate methods
// 상품 목록 조회
/**
 Gets the list of products registered in IAP Console.
 If the product list is nil, both products and error are nil.
 
 @param completionHandler The handler to execute after the list of products is complete.
 */
+ (void)requestProductsWithCompletionHandler:(nullable void (^)(NSArray<ToastOngateProduct *> *_Nullable products, NSError * _Nullable error))completionHandler;

// 미소비 결제 내역 조회
/**
 Gets the list of products that have not been paid out of the purchased consumable items.
 If the consumable purchase list is nil, both purchases and error are nil.
 
 @param completionHandler The handler to execute after the list of products is complete.
 */
+ (void)requestConsumablePurchasesWithCompletionHandler:(nullable void (^)(NSArray<ToastOngatePurchaseResult *> * _Nullable purchases, NSError * _Nullable error))completionHandler;

// 상품 구매
/**
 Purchase a product acquired through the request. The purchase result is returned to the delegate.
 
 @param product The product to purchase.
 */
+ (void)purchaseWithProduct:(ToastOngateProduct *)product;

#pragma mark - Sets debug mode and gets the version
// Debug 모드 설정
/**
 Sets whether to set debug mode.
 
 @param debugMode If `YES` the debugMode is enabled. If `NO` then the debugMode is disabled.
 
 @warning When releasing an app, you must disable debug mode.
 
 */
+ (void) setDebugMode:(BOOL)debugMode;

// SDK 버전 정보
/**
 Gets the version of SDK.
 
 @return The version of SDK.
 */
+ (NSString *)version;

@end

/**
 The delegate to be executed according to the purchase result.
 */
@protocol ToastOngatePurchaseDelegate <NSObject>

// 결제 성공
/**
 Called after the purchase has been successfully.
 
 @param purchase The purchase that successfully complete
 */
- (void)didReceivePurchaseResult:(ToastOngatePurchaseResult *)purchase;

// 결제 실패
/**
 Called after the purchase has been failure.
 
 @param productIdentifier The identifier of product that has been failure.
 @param error The error about the cause of the payment failure.
 */
- (void)didFailPuchaseProduct:(NSString * _Nullable)productIdentifier
                    withError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
