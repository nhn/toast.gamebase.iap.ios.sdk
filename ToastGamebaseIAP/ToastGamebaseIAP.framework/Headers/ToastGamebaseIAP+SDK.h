//
//  ToastGAmebaseIAP+SDK.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 16/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef REFLECTION_ONGATE
#else
#import <ToastOngate/ToastOngate.h>
#endif

#import "ToastGamebaseIAPConfiguration.h"
#import "ToastGamebaseProduct.h"
#import "ToastGamebaseProductsResponse.h"


@class ToastGamebasePurchase;

typedef void (^ToastGamebasePurchaseHandler)(NSString *_Nonnull store,
                                                   BOOL isSuccess,
                                                   ToastGamebasePurchase *_Nullable purchase,
                                                   NSString *_Nonnull productID,
                                                   NSError* _Nullable error);

@protocol ToastGamebaseInAppPurchaseDelegate <NSObject>

- (void)didReceivePurchaseResultForStore:(NSString *_Nonnull)store
                               isSuccess:(BOOL)isSuccess
                                purchase:(ToastGamebasePurchase *_Nullable)purchase
                               productID:(NSString * _Nonnull)productID
                                   error:(NSError *_Nullable)error;
@end

NS_ASSUME_NONNULL_BEGIN

@interface ToastGamebaseIAP : NSObject

+ (void)setDelegate:(id<ToastGamebaseInAppPurchaseDelegate>)delegate;

+ (void)initWithConfiguration:(ToastGamebaseIAPConfiguration *)configuration;

+ (void)initWithConfiguration:(ToastGamebaseIAPConfiguration *)configuration
                     delegate:(id<ToastGamebaseInAppPurchaseDelegate>)delegate;



+ (void)requestProductsForStore:(NSString *)store
          withCompletionHandler:(nullable void (^)(ToastGamebaseProductsResponse * _Nullable response, NSError * _Nullable error))completionHandler;

+ (void)requestConsumablePurchasesForStore:(NSString *)store
                     withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;

+ (void)purchaseForStore:(NSString *)store
                 product:(ToastGamebaseProduct *)product
   withCompletionHandler:(ToastGamebasePurchaseHandler)completionHandler;

+ (void)purchaseForStore:(NSString *)store
               productID:(NSString *)productID
   withCompletionHandler:(ToastGamebasePurchaseHandler)completionHandler;

//ToastIAP only
+ (void)restoreForStore:(NSString *)store
  withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;

+ (void)requestActivatedPurchasesForStore:(NSString *)store
                    withCompletionHandler:(nullable void (^)(NSArray<ToastGamebasePurchase *> * _Nullable purchases, NSError * _Nullable error))completionHandler;

//ToastIAP only && TCIAPurchase Migration
+ (void)processesIncompletePurchasesForStore:(NSString *)store
                       withCompletionHandler:(nullable void (^)(NSArray <ToastGamebasePurchase *> * _Nullable results, NSError * _Nullable error))completionHandler;

// Supprot Util
+ (void)consumeForStore:(NSString *)store
               purchase:(ToastGamebasePurchase *)purchase
  withCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler;

+ (void)setDebugMode:(BOOL)debugMode;

+ (NSString *)version;
@end

NS_ASSUME_NONNULL_END
