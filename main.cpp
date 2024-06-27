#include <iostream>
#include <list>
#include <regex>

enum class OrderType {
    GoodTillCancel,
    FillAndKill
};

enum class Side {
    Buy,
    Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo {
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderBookLevelInfos {
public:
    OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
        : bids_ {bids}
        , asks_ {asks} { }

    const LevelInfos& getBids() const { return bids_; }
    const LevelInfos& getAsks() const { return asks_; }

private:
    LevelInfos bids_;
    LevelInfos asks_;
};

class Order {
public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
        : orderType_ { orderType }
        , orderId_ { orderId }
        , side_ { side }
        , price_ { price }
        , initialQuantity_ { quantity }
        , remainingQuantity_ { quantity } {}

    OrderType getOrderType() const { return orderType_; }
    OrderId getOrderId() const { return orderId_; }
    Side getSide() const { return side_; }
    Price getPrice() const { return price_; }
    Quantity getInitialQuantity() const { return initialQuantity_; }
    Quantity getRemainingQuantity() const { return remainingQuantity_; }
    Quantity getFilledQuantity() const { return getInitialQuantity() - getRemainingQuantity(); }
    void Fill(Quantity quantity) {
        if (quantity > getRemainingQuantity()) {
            throw std::logic_error(std::regex_constants::format_default("Order ({}) cannot be filled more than its remaining quantity.", getOrderId()));
        }
        remainingQuantity_ -= quantity;
    }

private:
    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

class OrderModify {
public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
        : orderId_ { orderId }
        , side_ { side }
        , price_ { price }
        , quantity_ { quantity } {}

    OrderId getOrderId() const { return orderId_; }
    Side getSide() const { return side_; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return quantity_; }

    OrderPointer toOrderPointer(OrderType orderType) {
        return std::make_shared<Order>(orderType, getOrderId(), getSide(), getPrice(), getQuantity());
    }

private:
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity quantity_;
};



int main() {

    return 0;
}
